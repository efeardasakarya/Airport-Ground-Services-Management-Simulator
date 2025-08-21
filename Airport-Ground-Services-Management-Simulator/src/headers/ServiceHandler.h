#pragma once
#include <iostream>
#include "Service.h"
#include "Flight.h"
#include "GlobalLogger.h"

class ServiceHandler
{




public:

	void serviceHandler(Flight* landingFlight, bool adding);


	void fuelTaskHandler(Flight* landingFlight, bool adding);

	void cleaningTaskHandler(Flight* landingFlight, bool adding);

	void luggageTaskHandler(Flight* landingFlight, bool adding);

	GlobalLogger* logger =  GlobalLogger::getInstance();
	



};

