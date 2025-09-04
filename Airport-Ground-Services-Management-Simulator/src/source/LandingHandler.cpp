#include "LandingHandler.h"
#include "ServiceHandler.h"
#include "GlobalLogger.h"
#include "Flight.h"

#include <random>
#include <thread>
#include <chrono>
#include <memory>

// Use variables as local for prevent data races. Every thread uses his variables

thread_local std::optional<std::map<std::string, Flight>::node_type> localNode; // Keep one flightNumber and Flight from flightRecords map
thread_local Flight* localFlight = nullptr;
thread_local int localRemainLandTime = 0; // Counter for landing 

LandingHandler::LandingHandler()
{
	logger = GlobalLogger::getInstance();
	serviceHandler = ServiceHandler::getInstance();
}

LandingHandler::~LandingHandler()
{

}

int LandingHandler::randomNumberGenerator(int minimum, int maximum)
{
	static thread_local std::mt19937 range{ std::random_device{}() };
	return std::uniform_int_distribution<int>(minimum, maximum)(range);
}

void LandingHandler::landingProcess(std::map<std::string, Flight>& flightRecords)
{
	// 1) Get flight to node from flightRecords map and initial landing
	{
		std::scoped_lock lock(refLock); // mutex for prevent data-race
		if (!localNode)
		{
			if (!flightRecords.empty()) // 
			{
				// Get first element to node from map
				localNode.emplace(flightRecords.extract(flightRecords.begin()));
				localFlight = &localNode->mapped();

				// Pick a number between 4 and 30 and give to remainLandTime
				localRemainLandTime = randomNumberGenerator(4, 30);
				logger->important(localFlight->getFlightNumber() + " ---> landing started.");
			}
			else
			{
				return;
			}
		}
	}

	// 2) Simulate Landign
	while (localRemainLandTime > 0)
	{
		// Reduce land time 1 every seconds. 
		std::this_thread::sleep_for(std::chrono::seconds(1));
		--localRemainLandTime;  // --operator -> use value first and decrement later
	}
	// Log when fligt landed
	logger->important(localFlight->getFlightNumber() + " ---> landing completed.");

	// 3) Lock logger while getting input. Mute and ignore infos. Add important logs to queue and print after get input
	serviceHandler->serviceHandler(localFlight);

	// 4) Use smart pointer for hold the flight safe using shared_ptr.
	//    Move Flight to the shared_ptr groundedFlights by move from node. 
	std::shared_ptr<Flight> groundedFlight;
	{
		Flight moved = std::move(localNode->mapped());
		groundedFlight = std::make_shared<Flight>(std::move(moved));
	}
	// push groundedFlight to Grounded Flights inside the service handler
	serviceHandler->enqueueGroundedFlight(std::move(groundedFlight));

	// 5) Clear the local elements of the thread
	{
		std::scoped_lock lock(refLock);
		localNode.reset();
		localFlight = nullptr;
		localRemainLandTime = 0;
	}
}

int LandingHandler::hasWork(std::map<std::string, Flight>& flightRecords) 
{
	std::scoped_lock lock(refLock);
	return static_cast<int>(flightRecords.size());
}
