#pragma once
#include <map>
#include <thread>
#include <mutex> 
#include <optional>
#include <chrono>


#include "spdlog/spdlog.h"

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "GlobalLogger.h"
#include "Service.h" 
#include "ServiceHandler.h"




class LandingHandler
{


public:

	LandingHandler();

	void landingProcess(std::map<std::string, Flight>& flightRecords);

	int hasWork(std::map<std::string, Flight>& flightRecords);

private:

	FlightRecordsManager flightRecordManager;

	ServiceHandler serviceHandler;

	//Flight* landingFlight = nullptr;

	//std::optional<std::map<std::string, Flight>::node_type> currentNode;

	//int remainLandTime = 10;

	bool landingLoop = true;

	GlobalLogger* logger;

	std::mutex refLock;
	std::mutex timeLock;

	int randomNumberGenerator(int i, int  j);



};









