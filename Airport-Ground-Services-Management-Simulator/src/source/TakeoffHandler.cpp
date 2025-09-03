#include "TakeoffHandler.h"
#include "ServiceHandler.h"
#include "GlobalLogger.h"
#include "Flight.h"
#include "Service.h"                           // enumlar burada
#include "magic_enum/magic_enum.hpp"

#include <thread>
#include <chrono>
#include <vector>
#include <string>


// Constructor
TakeoffHandler::TakeoffHandler() {
	logger = GlobalLogger::getInstance();
	serviceHandler = ServiceHandler::getInstance();
}
// Destructor
TakeoffHandler::~TakeoffHandler() {}

// --------- Process Durations (Completely developer editeble) ---------
int TakeoffHandler::durationForLuggageTask(int luggage)
{
	// Get Luggage task by index. Look Service.h for indexes
	auto task = static_cast<LuggageTasks>(luggage);
	// Get process duration by task
	switch (task)
	{
	case LuggageTasks::LoadLuggage:
		return 3;
	case LuggageTasks::UnloadLuggage:
		return 3;
	case LuggageTasks::TransportLuggage:
		return 2;
	default:
		return 0;
	}
}
int TakeoffHandler::durationForCleaningTask(int cleaning)
{   // Get cleaning task by index. Look Service.h forindex
	auto task = static_cast<CleaningTasks>(cleaning);
	// Get process duration by task
	switch (task) {
	case CleaningTasks::Daily:
		return 2;
	case CleaningTasks::Weekly:
		return 3;
	case CleaningTasks::Monthly:
		return 4;
	case CleaningTasks::Yearly:
		return 5;
	default:
		return 0;
	}
}
int TakeoffHandler::durationForFuelTask(int fuel)
{
	// Get fuel task by index. Look Service.h for indexes
	auto task = static_cast<FuelTasks>(fuel);
	// Get process duration by task
	switch (task)
	{
	case FuelTasks::RefuelPlane:
		return 4;
	case FuelTasks::RefuelTank:
		return 3;
	case FuelTasks::TransportFuel:
		return 2;
	default:
		return 1;
	}
}

// --------- Processors ---------
void TakeoffHandler::runLuggageTasks(const std::shared_ptr<Flight>& flight) 
{
	//Get copy against data changes in while for auto working
 	auto luggage = flight->getLuggageTasks();
	for (auto tasks : luggage) 
	{
		// Get task name to a string for logging using magic enum library
		auto name = std::string(magic_enum::enum_name(tasks));
		// Start task process and log 
		logger->printInfo(flight->getFlightNumber() + " ---> Luggage/" + name + " started");
		// Wait as duration as got from durationForLuggageTask 
		std::this_thread::sleep_for(std::chrono::seconds(durationForLuggageTask(static_cast<int>(tasks))));
		// When time is up finish task and log
		logger->printInfo(flight->getFlightNumber() + " ---> Luggage/" + name + " completed");

		// Remove the task from flight when finished
		flight->removeDemandingServices(tasks);
	}
}

void TakeoffHandler::runCleaningTasks(const std::shared_ptr<Flight>& flight) 
{
	// Get copy againt data changes while for auto working
	auto cleaning = flight->getCleaningTasks();
	for (auto task : cleaning) 
	{
		// Get task name to a string for logging using magic enum library
		auto name = std::string(magic_enum::enum_name(task));
		// Start task process and log
		logger->printInfo(flight->getFlightNumber() + " ---> Cleaning/" + name + " started");
		// Wait as duration as got from durationForCleaningTask 
		std::this_thread::sleep_for(std::chrono::seconds(durationForCleaningTask(static_cast<int>(task))));
		// When time is up finish task and log
		logger->printInfo(flight->getFlightNumber() + " ---> Cleaning/" + name + " completed");

		// Remove the task from flight when finished
		flight->removeDemandingServices(task);
	}
}

void TakeoffHandler::runFuelTasks(const std::shared_ptr<Flight>& flight) 
{
	// Get copy againt data changes while for auto working
	auto fuel = flight->getFuelTasks();
	for (auto task : fuel) 
	{
		// Get task name to a string for logging using magic enum library
		auto name = std::string(magic_enum::enum_name(task));
		// Start task process and log
		logger->printInfo(flight->getFlightNumber() + " ---> Fuel/" + name + " started");
		// Wait as duration as got from durationForCleaningTask 
		std::this_thread::sleep_for(std::chrono::seconds(durationForFuelTask(static_cast<int>(task))));
		// When time is up finish task and log
		logger->printInfo(flight->getFlightNumber() + " ---> Fuel/" + name + " completed");

		// Remove the task from flight when finished
		flight->removeDemandingServices(task);
	}
}

// --------- Main Flow ---------
void TakeoffHandler::takeoffProcess() {
	// Get one flight object from groundedFlight queue and pop. So only one thread reach that flight and other flight move to the top.
	// FIFO. Due to pop next thread can reach next elements not always first 

	auto flight = serviceHandler->popGroundedFlight();

	if (!flight) 
	{
		logger->printError("popGroundedFlight() returned null flight.");
		return;
	}

	logger->important(flight->getFlightNumber() + " ---> ground services started.");

	// 2) Process services by lane. First handle luggages, cleaning , last fuel and flight takes off 
	runLuggageTasks(flight);
	runCleaningTasks(flight);
	runFuelTasks(flight);

	// 3) Takeoff 
	logger->important(flight->getFlightNumber() + " ---> all tasks have been completed.");
	logger->important(flight->getFlightNumber() + " ---> taking off.");

	// 4) Release runway for next flights
	serviceHandler->releaseRunway();
}
