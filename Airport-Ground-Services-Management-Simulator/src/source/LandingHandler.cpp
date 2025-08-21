#include "LandingHandler.h"

LandingHandler::LandingHandler()
{

}


void LandingHandler::landingProcess(std::map<std::string, Flight>& flightRecords)
{
	auto it = flightRecords.begin();

	if (logger == nullptr)
	{
		logger = GlobalLogger::getInstance();
	}

	while (landingLoop)
	{

		if (landingFlight == nullptr)
		{
			if (it == flightRecords.end())
			{
				logger->printInfo("Tum ucuslar inis yapti, program sonlandiriliyor.");
				landingLoop = false;
				break;

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
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	}

}

