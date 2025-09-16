#include "TakeoffHandler.h"

#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <atomic>

#include "ServiceHandler.h"
#include "GlobalLogger.h"
#include "Flight.h"
#include "Service.h"        
#include "magic_enum/magic_enum.hpp"

// Constructor
TakeoffHandler::TakeoffHandler()
{
	logger = GlobalLogger::getInstance();
	serviceHandler = ServiceHandler::getInstance();
}

// Destructor
TakeoffHandler::~TakeoffHandler()
{
	checkThreads(true);
}

// --------- Processors ---------
void TakeoffHandler::runLuggageTasks(const std::shared_ptr<Flight>& flight)
{
	auto now = SimulationTime::getInstance()->clockMinute;  // Get system clock
	auto luggage = flight->getLuggageTasks();  

	// Get luggage tasks from flight class
	for (const auto& [task, endTime] : luggage)
	{
		auto name = std::string(magic_enum::enum_name(task));

		// Complete and remove task from flight
		if (now >= endTime)
		{
			logger->printInfo(flight->getFlightNumber() + " ---> Luggage/" + name + " completed");
			flight->removeDemandingServices(task);
		}

	}
}

void TakeoffHandler::runCleaningTasks(const std::shared_ptr<Flight>& flight)
{
	auto now = SimulationTime::getInstance()->clockMinute; // Get system clock
	auto cleaning = flight->getCleaningTasks();

	// Get cleaning tasks from flight class
	for (const auto& [task, endAt] : cleaning)
	{
		auto name = std::string(magic_enum::enum_name(task));
		// Complete and remove task from flight
		if (now >= endAt)
		{
			logger->printInfo(flight->getFlightNumber() + " ---> Cleaning/" + name + " completed ");
			flight->removeDemandingServices(task);
		}

	}
}

void TakeoffHandler::runFuelTasks(const std::shared_ptr<Flight>& flight)
{
	auto now = SimulationTime::getInstance()->clockMinute; // Get system clock
	auto fuel = flight->getFuelTasks();

	// Get fuel tasks from flight class
	for (const auto& [task, endAt] : fuel)
	{
		auto name = std::string(magic_enum::enum_name(task));

		// Complete and remove task from flight
		if (now >= endAt) 
		{
			logger->printInfo(flight->getFlightNumber() + " ---> Fuel/" + name + " completed");
			flight->removeDemandingServices(task);
		}

	}
}

// --------- Main Flow ---------
void TakeoffHandler::takeoffProcess()
{
	std::shared_ptr<Flight> flight;

	if (!serviceHandler->waitAndPopOne(flight) || !flight) return;

	//Task processors
	runLuggageTasks(flight);
	runCleaningTasks(flight);
	runFuelTasks(flight);

	// Check that all tasks are complete
	const bool allDone =
		flight->getDemandingServices().empty() &&
		flight->getFuelTasks().empty() &&
		flight->getLuggageTasks().empty() &&
		flight->getCleaningTasks().empty();

	if (allDone)
	{
		logger->important(flight->getFlightNumber() + " ---> all tasks have been completed.");
		logger->important(flight->getFlightNumber() + " ---> taking off.");
		serviceHandler->releaseRunway();
	}
	else 
	{
		// If all tasks don't complete push the flight to the queue again 
		serviceHandler->pushGroundedFlight(flight); 
	}
}

// --------- Thread Handler ---------
void TakeoffHandler::checkThreads(bool finalize)
{
	std::lock_guard<std::mutex> lk(threadsMutex);

	for (int i = 0; i < threads.size(); )
	{
		if (doneThreads[i] && doneThreads[i]->load(std::memory_order_acquire))
		{
			if (threads[i].joinable())
			{
				threads[i].join();
			}
			threads.erase(threads.begin() + i);
			doneThreads.erase(doneThreads.begin() + i);
		}
		else
		{
			++i;
		}
	}

	if (!finalize && threads.empty())
	{
		for (int k = 0; k < 2; ++k)
		{
			auto flag = std::make_shared<std::atomic_bool>(false);
			std::thread t([this, flag]()
				{
					this->takeoffProcess();
					flag->store(true, std::memory_order_release);
				});
			threads.push_back(std::move(t));
			doneThreads.push_back(std::move(flag));
		}
	}
}
