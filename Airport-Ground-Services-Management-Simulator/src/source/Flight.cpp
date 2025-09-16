#include "Flight.h"
#include "Service.h"


Flight::Flight(const std::string& FlightNumber, const std::string& AirLine, const std::string& LandingTime)
{
	// Give essential Flight informations in constructor. Essentials will get from file
	flightNumber = FlightNumber;
	airLine = AirLine;
	landingTime = LandingTime;
	simulationTime = SimulationTime::getInstance();
}

// Get Methods ( Const at beggining and end means this functions only readable
const std::string& Flight::getFlightNumber() const
{
	return flightNumber;
}
const std::string& Flight::getAirLine() const
{
	return airLine;
}
const std::string& Flight::getLandingTime() const
{
	return landingTime;
}

//Task Getters

const std::unordered_set<Service> Flight::getDemandingServices() const
{
	return demandingServices;
}
const std::unordered_map<FuelTasks, int> Flight::getFuelTasks() const
{
	return fuelTasks;
}
const std::unordered_map<LuggageTasks, int> Flight::getLuggageTasks() const
{
	return luggageTasks;
}
const std::unordered_map<CleaningTasks, int > Flight::getCleaningTasks() const
{
	return cleaningTasks;
}


// Change flights informations if necessary
void Flight::setFlightNumber(const std::string& newFlightNumber)
{
	flightNumber = newFlightNumber;
}

void Flight::setAirLine(const std::string& newAirLine)
{
	airLine = newAirLine;
}

void Flight::setLandingTime(const std::string& newLandingTime)
{
	landingTime = newLandingTime;
}



// --- add ---
void Flight::addDemandingServices(CleaningTasks t)
{
	// sr’yi param olarak alsak da güvenli olan type’tan seti seçmek:
	demandingServices.insert(Service::Cleaning);
	cleaningTasks.emplace(t, simulationTime->clockMinute + durationForCleaningTask(t));
}

void Flight::addDemandingServices(FuelTasks t)
{
	demandingServices.insert(Service::Fuel);
	fuelTasks.emplace(t, simulationTime->clockMinute + durationForFuelTask(t));
}

void Flight::addDemandingServices(LuggageTasks t)
{
	demandingServices.insert(Service::Luggage);
	luggageTasks.emplace(t, simulationTime->clockMinute + durationForLuggageTask(t));
}

// --- remove ---
void Flight::removeDemandingServices(CleaningTasks t)
{
	cleaningTasks.erase(t);
	if (cleaningTasks.empty())
		demandingServices.erase(Service::Cleaning);
}

void Flight::removeDemandingServices(FuelTasks t)
{
	fuelTasks.erase(t);
	if (fuelTasks.empty())
		demandingServices.erase(Service::Fuel);
}

void Flight::removeDemandingServices(LuggageTasks t)
{
	luggageTasks.erase(t);
	if (luggageTasks.empty())
		demandingServices.erase(Service::Luggage);
}






