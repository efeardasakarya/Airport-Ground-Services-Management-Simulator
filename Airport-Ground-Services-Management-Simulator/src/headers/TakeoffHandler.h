#pragma once

#include <map>

#include "spdlog/spdlog.h"

#include "Flight.h"
#include "FlightRecordsManager.h"
#include "GlobalLogger.h"
#include "Service.h"
#include "ServiceHandler.h"



class TakeoffHandler
{
private:

	FlightRecordsManager flightRecordManager;

	ServiceHandler serviceHandler;

	Flight* takeoffFlight = nullptr;

	int remainTakeoffTime = 10;

	bool takeoffLoop = true;

	GlobalLogger* logger;



public:

	TakeoffHandler();

	void takeoffProcess(std::map<std::string, Flight>& flightRecords);
};

