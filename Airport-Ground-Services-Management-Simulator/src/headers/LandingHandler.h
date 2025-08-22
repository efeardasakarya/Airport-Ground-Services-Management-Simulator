#pragma once
#include <map>

#include "spdlog/spdlog.h"

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "GlobalLogger.h"
#include "Service.h"
#include "ServiceHandler.h"



class LandingHandler
{

private:

	FlightRecordsManager flightRecordManager;

	ServiceHandler serviceHandler;

	Flight* landingFlight = nullptr;

	int remainLandTime = 10;

	bool landingLoop = true;

	GlobalLogger* logger;
	
	

public:

	LandingHandler();
	
	void landingProcess(std::map<std::string, Flight>& flightRecords);





};









