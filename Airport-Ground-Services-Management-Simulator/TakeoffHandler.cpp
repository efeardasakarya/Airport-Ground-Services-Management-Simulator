#include "TakeoffHandler.h"

TakeoffHandler::TakeoffHandler()
{
	logger = GlobalLogger::getInstance();
}


void TakeoffHandler::takeoffProcess(std::map<std::string, Flight>& flightRecords)
{

	auto it = flightRecords.begin();

	while (takeoffLoop)
	{

		if (takeoffFlight == nullptr)
		{
			if (it == flightRecords.end())
			{
				logger->printInfo("Tum ucuslar kalkis yapti, program sonlandiriliyor.");
				takeoffLoop = false;
				break;
			}

			else
			{
				takeoffFlight = &it->second;
			}


		}


		else
		{
			if (takeoffFlight->getDemandingServices().empty() )
			{
				logger->printInfo("Flight " + takeoffFlight->getFlightNumber() + " has taken off");
				takeoffFlight = nullptr;
			}

			else
			{

			}





		}





		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	}






}
