// Airport-Ground-Services-Management-Simulator.cpp ,

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "GlobalLogger.h"
#include "Service.h"
#include "ServiceHandler.h"
#include "LandingHandler.h"
#include <queue>
#include <thread>
#include <chrono>
#include <sstream>






int main()
{

	FlightRecordsManager flightRecordManager;
	ServiceHandler serviceHandler;
	LandingHandler landingHandler;
	


	//Creating and register logger
	auto logger = GlobalLogger::getInstance(); // Create and register named "asyncLogger"
	logger->asyncMultiSink();
	logger->printInfo("asyncLogger has been created");


	//Read file and create flight objects
	std::map<std::string, Flight>& flightRecords = flightRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");

	
	landingHandler.landingProcess(flightRecords);

	     
	

}


