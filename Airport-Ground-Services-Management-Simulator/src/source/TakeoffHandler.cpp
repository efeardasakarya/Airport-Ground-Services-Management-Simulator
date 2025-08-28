#include "TakeoffHandler.h"

#include "magic_enum/magic_enum.hpp"

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
			if ( !(takeoffFlight->getDemandingServices().count(Service::Cleaning) >0 || takeoffFlight->getDemandingServices().count(Service::Fuel) || takeoffFlight->getDemandingServices().count(Service::Luggage) )  )
			{
				logger->printInfo("Flight " + takeoffFlight->getFlightNumber() + " has taken off");
				it++;
				takeoffFlight = nullptr;
			}

			else
			{

				if (takeoffFlight->getDemandingServices().count(Service::Cleaning) > 0)
				{
					for (auto& cleaningTasks : takeoffFlight->getCleaningTasks()  )
					{
						takeoffFlight->removeDemandingServices(cleaningTasks);
						logger->printInfo(std::string(magic_enum::enum_name(cleaningTasks)) + " task completed");

					}
					logger->printInfo("Cleaning tasks completed");
				}

				else if (takeoffFlight->getDemandingServices().count(Service::Fuel) > 0)
				{
					for (auto& fuelTasks : takeoffFlight->getFuelTasks())
					{
						takeoffFlight->removeDemandingServices(fuelTasks);
						logger->printInfo(std::string(magic_enum::enum_name(fuelTasks)) + " task completed");
					}
					logger->printInfo("Fuel tasks completed");
				}
				else if (takeoffFlight->getDemandingServices().count(Service::Luggage) > 0)
				{
					for (auto& luggageTasks : takeoffFlight->getLuggageTasks())
					{
						takeoffFlight->removeDemandingServices(luggageTasks);
						logger->printInfo(std::string(magic_enum::enum_name(luggageTasks)) + " task completed");
					}
					logger->printInfo("Luggage tasks completed");
				}

			}

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	}






}