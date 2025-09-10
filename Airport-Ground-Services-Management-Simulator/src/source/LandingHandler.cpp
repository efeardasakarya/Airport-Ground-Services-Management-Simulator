#include <random>
#include <thread>
#include <chrono>
#include <memory>

#include "LandingHandler.h"
#include "ServiceHandler.h"
#include "GlobalLogger.h"
#include "Flight.h"

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

void LandingHandler::landingProcess(Flight landingFlight)
{
	auto groundedFlight = std::make_shared<Flight>(std::move(landingFlight));

	logger->important("Flight " + groundedFlight->getFlightNumber() + " ---> landed.");

	// 3) Lock logger while getting input. Mute and ignore infos. Add important logs to queue and print after get input
	serviceHandler->serviceHandler(groundedFlight);

	
}