// Airport-Ground-Services-Management-Simulator.cpp ,

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "GlobalLogger.h"
#include "Service.h"
#include "ServiceHandler.h"
#include <queue>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>





int main()
{
	FlightRecordsManager flightRecordManager;
	ServiceHandler serviceHandler;


	//Creating and register logger
	auto logger = GlobalLogger::getInstance(); // Create and register named "asyncLogger"
	logger->asyncMultiSink();
	logger->printInfo("asyncLogger has been created");


	//Read file and create flight objects
	std::map<std::string, Flight>& flightRecords = flightRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");

	// Local Variables
	Flight* landingFlight = nullptr;
	Flight* takeofFlight = nullptr;
	auto it = flightRecords.begin();
	int remainLandTime = 10;
	bool landingLoop = true;
	



	while (landingLoop) {


		if (landingFlight == nullptr)
		{
			if (it == flightRecords.end()) {
				logger->printInfo("Tum ucuslar inis yapti, program sonlandiriliyor.");
				landingLoop = false;
				
			}
			else
			{
				landingFlight = &it->second;
			}
		}

		else
		{
			if (remainLandTime == 0)
			{
				logger->printInfo("Flight " + landingFlight->getFlightNumber() + " has landed");

				serviceHandler.serviceHandler(landingFlight, true);

				it++;
				landingFlight = nullptr;
				remainLandTime = 10;
			}
			else
			{
				logger->printInfo("Flight " + landingFlight->getFlightNumber() + " will land in " + std::to_string(remainLandTime) + " seconds");
				remainLandTime--;
			}
		}

		// 1 saniye bekle
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}





}


