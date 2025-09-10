#include "ServiceHandler.h"

#include <iostream>
#include <string>
#include <utility>
#include <cctype>

#include "GlobalLogger.h"
#include "Flight.h"
#include "Service.h"




// Constructor
ServiceHandler::ServiceHandler()
{
	logger = GlobalLogger::getInstance();

}
//Destructor
ServiceHandler::~ServiceHandler() = default;

// ---------- Runway Management (thread-safe & Atomic)  ----------

bool ServiceHandler::tryBookRunway()
{
	// Get number of available runways
	int currentRunways = availableRunway.load(std::memory_order_relaxed);

	while (currentRunways > 0) // Loop while at least one runway is available 
	{
		// Compare values load before loop and current. If same decrease currentRunways 1 ane update the memory
		// compare weak ---> Weak cause spurios failre but we compansate it with loop. Just try again
		// std::memory_order_acq_rel --> Memory order used in succes. Read the writtends before and publish the writtens
		//std::memory_order_relaxed  --> Memory order used in failure. Try again the loop in failure. Don't use unnecessasry barriers = good for performance

		if (availableRunway.compare_exchange_weak(currentRunways, currentRunways - 1, std::memory_order_acq_rel, std::memory_order_relaxed))
		{
			logger->printInfo("Runway booked. Remaining available runway count: " + std::to_string(availableRunway.load()));
			return true;
		}
		// When CAS failed -> continue loop  , when CAS succes -> finish funciton with true value
	}
	return false;
}

void ServiceHandler::releaseRunway()
{
	//fetch_add -> Read old value of availableRunway. 
	//fetch_add -> Add x and set as new value 
	//fetch_add ->  Return old value

	// In this funciton we update the availableRunway variable and log the newRunwayCount as available runway count. But in logger
	// we add as x because fetch_add return the old value. So when added the x we can get the current value of available runways
	int x = 1;
	int newRunwayCount = availableRunway.fetch_add(x, std::memory_order_acq_rel) + x;
	logger->printInfo("Runway released. Remaining: " + std::to_string(newRunwayCount));
}

int ServiceHandler::getAvailableRunwayCount() const
{
	return availableRunway.load(std::memory_order_relaxed);
}

// ---------- Grounded Flights Queue (thread-safe) ----------

bool ServiceHandler::waitAndPopOne(std::shared_ptr<Flight>& out)
{
	std::unique_lock<std::mutex> lock(groundedMtx);
	groundedCv.wait(lock, [&] { return !groundedFlights.empty(); });

	out = groundedFlights.front();
	groundedFlights.pop();
	return true;
}

/*
std::shared_ptr<Flight> ServiceHandler::popGroundedFlight()
{
	// When services are finished. Flight takes off and pop from groundedFlights so other flight can be used by takeoffHandler 
	std::unique_lock<std::mutex> lock(groundedMtx);
	// groundedCV.wait --->  if groundedFlights is not empty wake up a takeoffHandler to process services
	groundedCv.wait(lock, [&] { return !groundedFlights.empty(); });
	// Take the first element of the groundedFlights and copy to a flight object. After copying pop so takeoffHandler can get next flight. FIFO . First process first flight
	auto flight = groundedFlights.front();
	groundedFlights.pop();
	return flight;
}
*/

void ServiceHandler::enqueueGroundedFlight(std::shared_ptr<Flight> flight)
{
	{
		std::lock_guard<std::mutex> lock(groundedMtx);
		groundedFlights.push(std::move(flight)); // Uçuş kuyrukta tutulur
	}

	groundedCv.notify_one(); // Kuyruktan uçuş almak için bekleyen bir thread’i uyandır
}


// ---------- Interactive service planner ----------

static std::string readLine(const std::string& userInput)
{
	//print message for get input like : " Please choose -> y or n "
	std::cout << userInput << std::flush;
	// Get input from user like y or n or 1,2,3 
	std::string input;
	std::getline(std::cin, input);
	return input;
}

static bool askYesNo(const std::string& userInput) // Function for add service or pass or end service adding
{
	while (true)
	{
		// First print message to console like : "Do you want add any service (y/n)? "
		// and get user input using readLine function
		auto input = readLine(userInput + " (y/n): ");
		if (!input.empty())
		{
			// convert string to one character end make low case as 'n' or 'y'
			char c = static_cast<char>(std::tolower(input[0]));
			if (c == 'y') return true;
			if (c == 'n') return false;
		}
		std::cout << "Please input y(yes) or n(no).\n";
	}
}

static int askInt(const std::string& message, int minimum, int maximum)
{
	while (true)
	{
		// Print message to console with readLine like : "Please choose service [0-2]"
		// And get input using readLine again
		auto scale = readLine(message + " [" + std::to_string(minimum) + "-" + std::to_string(maximum) + "]: ");
		try
		{
			// Try convert string to integer and give the value.
			int value = std::stoi(scale);
			// if value is between maximum and minimum finish the function.
			if (value >= minimum && value <= maximum) return value;
		}
		catch (...)
		{

		}
		std::cout << "Gecersiz deger.\n";
	}
}

void ServiceHandler::serviceHandler(const std::shared_ptr<Flight>& flight)
{
	if (flight == nullptr) return;

	// Only one thread can get input from user
	std::unique_lock<std::mutex> inputLock(userInputMtx);
	 
	

	// Mute and ignore info messages , add queue to important messages and print later
	logger->lockInput();

	std::cout << "\n=== Ground Service Planner for flight: " << flight->getFlightNumber() << " ===\n";

	while (true)
	{
		// If user says no end break loop 
		if (!askYesNo("Do you want add/remove service to " + flight->getFlightNumber()))
		{
			enqueueGroundedFlight(flight);
			
			break;
		}
		// If user says yes continue submenu
		std::cout << "Choose service type:\n"
			<< "  0) Luggage\n"
			<< "  1) Cleaning\n"
			<< "  2) Fuel\n";
		// give group variable to switch for which service add/remove
		int group = askInt("Please choose Service Type ", 0, 2);

		std::cout << "Add/Remove:\n"
			<< "  0) Add\n"
			<< "  1) Remove\n";
		// if op equals zero that mean adding yes and add service , else 1 will remove service
		int op = askInt("Add Service or Remove Service ? ", 0, 1);
		bool adding = (op == 0);

		switch (group)
		{
		case 0: 
			this->luggageTaskHandler(flight.get(), adding);  
			break;
		case 1: 
			this->cleaningTaskHandler(flight.get(), adding); 
			break;
		case 2: 
			this->fuelTaskHandler(flight.get(), adding);     
			break;
		default:
			std::cout << "Gecersiz secim.\n";
			break;
		}
	}

	std::cout << "Service adding/removing completed.\n";

	// Flush the important messages and unmute the infos 
	logger->unlockInput();


}

// ---------- Per-group helpers ----------

void ServiceHandler::fuelTaskHandler(Flight* landingFlight, bool adding)
{
	if (!landingFlight)
	{
		return;
	}

	// Initial value for task to avoid undefined warnings
	FuelTasks task = FuelTasks::NoneFuel;

	while (true)
	{
		std::cout
			<< "\n[FUEL] Choose Fuel Service:\n"
			<< "  0) Refuel Plane\n"
			<< "  1) Refuel Tank\n"
			<< "  2) TransportFuel\n";
		// Get value between 0-2 to choose task
		int fuelInput = askInt("Secim", 0, 2);

		switch (fuelInput)
		{
		case 0:
			task = FuelTasks::RefuelPlane;
			break;
		case 1:
			task = FuelTasks::RefuelTank;
			break;
		case 2:
			task = FuelTasks::TransportFuel;
			break;
		default:
			std::cout << "Invalid input.\n";
			continue;
		}
		break;
	}
	//add or remove service indexed by adding
	if (adding)
	{
		landingFlight->addDemandingServices(task);
	}
	else
	{
		landingFlight->removeDemandingServices(task);
	}
}

void ServiceHandler::cleaningTaskHandler(Flight* landingFlight, bool adding)
{
	if (!landingFlight)
	{
		return;
	}
	// Initial value for task to avoid undefined warnings 
	CleaningTasks task = CleaningTasks::NoneCleaning;

	while (true)
	{
		std::cout
			<< "\n[CLEANING] Choose Cleaning Service:\n"
			<< "  0) Daily\n"
			<< "  1) Weekly\n"
			<< "  2) Monthly\n"
			<< "  3) Yearly\n";
		int cleaningInput = askInt("Secim", 0, 3);
		// Get value between 0-3 to choose task 
		switch (cleaningInput)
		{
		case 0:
			task = CleaningTasks::Daily;
			break;
		case 1:
			task = CleaningTasks::Weekly;
			break;
		case 2:
			task = CleaningTasks::Monthly;
			break;
		case 3:
			task = CleaningTasks::Yearly;
			break;
		default:
			std::cout << "Invalid choose.\n";
			continue;
		}
		break;
	}
	// add or remove service indexed by adding
	if (adding)
	{
		landingFlight->addDemandingServices(task);
	}
	else
	{
		landingFlight->removeDemandingServices(task);
	}
}

void ServiceHandler::luggageTaskHandler(Flight* landingFlight, bool adding)
{
	if (!landingFlight)
	{
		return;
	}
	// Initial value for task to avoid ındefined warnings
	LuggageTasks task = LuggageTasks::NoneLuggage;

	while (true)
	{
		std::cout
			<< "\n[LUGGAGE] Choose Luggage Service:\n"
			<< "  0) Load Luggage\n"
			<< "  1) Unload Luggage\n"
			<< "  2) TransportLuggage\n";
		int luggageInput = askInt("Secim", 0, 2);
		// Get value between 0-2 to choose task
		switch (luggageInput)
		{
		case 0: task = LuggageTasks::LoadLuggage;       break;
		case 1: task = LuggageTasks::UnloadLuggage;     break;
		case 2: task = LuggageTasks::TransportLuggage;  break;
		default:
			std::cout << "Invalid choose.\n";
			continue;
		}
		break;
	}
	// add/remove service indexed by adding
	if (adding)
	{
		landingFlight->addDemandingServices(task);
	}
	else {
		landingFlight->removeDemandingServices(task);
	}
}
