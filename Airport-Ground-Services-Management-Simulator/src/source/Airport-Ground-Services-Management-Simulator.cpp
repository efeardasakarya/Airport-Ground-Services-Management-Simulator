#include <map>
#include <string>
#include <thread>
#include <utility>
#include <sstream>


#include "Flight.h"
#include "GlobalLogger.h"
#include "FlightRecordsManager.h"
#include "ServiceHandler.h"
#include "LandingHandler.h"
#include "TakeoffHandler.h"


LandingHandler landingHandler;
TakeoffHandler takeoffHandler;

constexpr int takeoffThreadCount = 2;



struct Time
{
	int hour;
	int minute;

	Time(int hour = 0, int minute = 0) : hour(hour), minute(minute)
	{

	}
};

// New operator for compare time structs for cleaner code.
constexpr bool operator==(const Time& a, const Time& b)
{
	return a.hour == b.hour && a.minute == b.minute;

}

// Get flight landing time and convert to minutes for compare in main function easily
// For example : landing time 3.20 -> 200 minute. When the clock variable is 200 flight land.
int convertLandingTimeToMinute(const std::string& time)
{
	int hour = 0;
	int minute = 0;
	char dot = 0;
	std::stringstream seperate(time);
	seperate >> hour >> dot >> minute;

	return (hour * 60) + minute;
}

//Conver minutes to hour unit for std::cout or logger->info()
Time calculateTime(int counter)
{
	return Time(counter / 60, counter % 60);
}

void initalizeTakeoffThreads()
{
	for (int i = 0; i < takeoffThreadCount; ++i) {
		std::thread([&]()
			{
				//Regular consumer
				while (true)
				{
					takeoffHandler.takeoffProcess();
				}
			}).detach();
	}
}


int main()
{
	// Clock start at 00.00
	int clock = 0;

	// Flights arriving at the scheduled time are held here. 
	// Use deque for pop_front. So first arrived fligt landed first
	std::deque<Flight> flightWillLand;

	// Class read file and create flight objects
	FlightRecordsManager flighRecordManager;

	// Register file. Read all flight infos and hold in a map indexin by Flight Numbers.

	std::map<std::string, Flight> flightRecords = flighRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");

	GlobalLogger::getInstance()->important("Simulator starting...");

	initalizeTakeoffThreads();

	// 24 hour = 1440 minute 
	// Check landing times every minute
	while (clock < 1440)
	{
		//Check all flight list one-by-one
		// Get reference by & for block unnecessary copying
		for (const auto& [flightNumber, flightObject] : flightRecords)
		{
			// if system hour and landing hour is equal
			if (clock == convertLandingTimeToMinute(flightObject.getLandingTime()))
			{

				flightWillLand.emplace_back(flightObject);

			}
		}

		// Check available runways (Only 2 flight can land at the same time)
		while (!flightWillLand.empty() && ServiceHandler::getInstance()->tryBookRunway())
		{
			// Get first waiting flight and land
			landingHandler.landingProcess(std::move(flightWillLand.front()));
			flightWillLand.pop_front();
		}

		clock++;
		std::cout << calculateTime(clock).hour << ":" << calculateTime(clock).minute << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}
