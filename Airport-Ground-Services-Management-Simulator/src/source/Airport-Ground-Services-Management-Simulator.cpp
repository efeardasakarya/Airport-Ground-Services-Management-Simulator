#include <map>
#include <string>
#include <thread>
#include <utility>
#include <sstream>
#include <queue>


#include "Flight.h"
#include "GlobalLogger.h"
#include "FlightRecordsManager.h"
#include "ServiceHandler.h"
#include "LandingHandler.h"
#include "TakeoffHandler.h"
#include "SimulationTime.h"

LandingHandler landingHandler;
TakeoffHandler takeoffHandler;
SimulationTime* simulationTime = SimulationTime::getInstance();
GlobalLogger* logger = GlobalLogger::getInstance();
ServiceHandler* serviceHandler = ServiceHandler::getInstance();


int main()
{

	// Flights arriving at the scheduled time are held here. 
	// Use deque for pop_front. So first arrived fligt landed first
	std::queue<Flight> flightWillLand;

	// Class read file and create flight objects
	FlightRecordsManager flighRecordManager;

	// Register file. Read all flight infos and hold in a map indexin by Flight Numbers.

	std::map<std::string, Flight> flightRecords = flighRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");

	logger->important("Simulator starting...");

	

	// 24 hour = 1440 minute 
	// Check landing times every minute
	while (simulationTime->clockMinute < simulationTime->loopDuration)
	{
		takeoffHandler.checkThreads();
		//Check all flight list one-by-one
		// Get reference by & for block unnecessary copying
		for (const auto& [flightNumber, flightObject] : flightRecords)
		{
			// if system hour and landing hour is equal
			if (simulationTime->clockMinute == simulationTime->convertLandingTimeToMinute(flightObject.getLandingTime()))
			{

				flightWillLand.emplace(flightObject);
				

			}
		}

		// Check available runways (Only 2 flight can land at the same time)
		while (!flightWillLand.empty() && serviceHandler->tryBookRunway())
		{
			// Get first waiting flight and land
			landingHandler.landingProcess(std::move(flightWillLand.front()));
			flightWillLand.pop();
			//x
			
		}

		simulationTime->clockMinute++;
		SimulationTime::ClockTime time;

		//When simulation end
		if (simulationTime->clockMinute == 1440)
		{
			//Make clock 00:00
			simulationTime->clockMinute = 0;

			time = simulationTime->calculateTime(simulationTime->clockMinute);

			std::cout << time.hour << ":" << time.minute << std::endl;

			//delete all threads and don't create ew
			takeoffHandler.checkThreads(true);

			return 0;

		}


		time = simulationTime->calculateTime(simulationTime->clockMinute);

		std::cout << time.hour << ":" << time.minute << std::endl;

		
	}

}
