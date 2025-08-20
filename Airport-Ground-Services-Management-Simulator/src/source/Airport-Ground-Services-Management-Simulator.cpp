// Airport-Ground-Services-Management-Simulator.cpp ,

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "GlobalLogger.h"
#include "CleaningService.h"
#include "FuelService.h"
#include "LuggageService.h"
#include <queue>





int main()
{
	FlightRecordsManager flightRecordManager;
	std::queue<GroundService*> services;

	std::map<int, std::string> staffList;
	staffList[111] = "Staff1";
	staffList[222] = "Staff2";
	staffList[333] = "Staff3";
	staffList[444] = "Staff4";




	//Creating and register logger
	auto logger = GlobalLogger::getInstance(); // Create and register named "asyncLogger"
	logger->asyncMultiSink();
	logger->printInfo("asyncLogger has been created");


	//Read file and create flight objects
	std::map<std::string, Flight> & records = flightRecordManager.InitializeFlightRecordsManager("data/flight_program.csv"); 
	
	for (auto& [_,value] : records)
	{
		if (value.getFlightNumber()[0] == 'E')
		{
			value.setDemandingService(Clenaning);
			services.push(new CleaningService(staffList, 4));


		}

		else if (value.getFlightNumber()[0] == 'J')
		{
			value.setDemandingService(Lugagge);
			services.push(new LuggageService(staffList, 4));
		}


		else
		{
			value.setDemandingService(Fuel);
			services.push(new FuelService(staffList, 4));

		}
	

	}

 
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
