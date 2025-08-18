// Airport-Ground-Services-Management-Simulator.cpp ,

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "Logger.h"






int main()
{
	FlightRecordsManager flightRecordManager;

	flightRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");

	Logger logger;
	logger.createMultiSink();

	Logger asyncLogger;
	asyncLogger.asyncMultiSink();

	for (int i=0 ; i< 8191; i++)
	{
		asyncLogger.printInfo("asyncLogger has been worked", "asyncLogger");
	}

 
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
