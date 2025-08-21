#pragma once
#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "GlobalLogger.h"
#include "Service.h"
#include "ServiceHandler.h"
#include <map>


class LandingHandler
{

private:

	FlightRecordsManager flightRecordManager;
	ServiceHandler serviceHandler;
	
	Flight* landingFlight = nullptr;
	Flight* takeofFlight = nullptr;

	
	int remainLandTime = 10;
	bool landingLoop = true;
	GlobalLogger* logger;
	
	

public:

	LandingHandler();
	
	void landingProcess(std::map<std::string, Flight>& flightRecords);





};









