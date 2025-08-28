// Airport-Ground-Services-Management-Simulator.cpp 
// 
//C++ Headers

#include <thread>
#include <chrono>

#include "magic_enum/magic_enum.hpp"
#include "spdlog/spdlog.h"

#include "FlightRecordsManager.h"
#include "GlobalLogger.h"
#include "ServiceHandler.h"
#include "LandingHandler.h"
#include "TakeoffHandler.h"







int main()
{

	FlightRecordsManager flightRecordManager;
	ServiceHandler serviceHandler;
	LandingHandler landingHandler;
	TakeoffHandler takeoffHandler;



	//Creating and register logger
	auto logger = GlobalLogger::getInstance(); // Create and register named "asyncLogger"
	logger->asyncMultiSink();
	logger->printInfo("asyncLogger has been created");


	//Read file and create flight objects
	std::map<std::string, Flight>& flightRecords = flightRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");


	while (true)
	{


		if (landingHandler.hasWork(flightRecords) > 1)
		{
			std::jthread t1([&] { landingHandler.landingProcess(flightRecords); });
			std::jthread t2([&] { landingHandler.landingProcess(flightRecords); });
		}

		else if (landingHandler.hasWork(flightRecords) == 1)
		{
			std::jthread t1([&] { landingHandler.landingProcess(flightRecords); });
		}


		else
		{
			break;
		}
	}




	//takeoffHandler.takeoffProcess(flightRecords);

}


