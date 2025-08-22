#pragma once
#pragma once
#include "Flight.h"
#include "FlightRecordsManager.h"
#include "spdlog/spdlog.h"
#include "GlobalLogger.h"
#include "Service.h"
#include "ServiceHandler.h"
#include <map>


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

