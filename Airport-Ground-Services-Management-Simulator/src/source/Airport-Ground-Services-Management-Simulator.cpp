// Airport-Ground-Services-Management-Simulator.cpp ,

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "GlobalLogger.h"






int main()
{
	FlightRecordsManager flightRecordManager;

	//create Logger
	auto logger = GlobalLogger::getInstance(); // Create and register named "asyncLogger"
	logger->asyncMultiSink();
	logger->printInfo("asyncLogger has been created");


	flightRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");

	
	



 
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
