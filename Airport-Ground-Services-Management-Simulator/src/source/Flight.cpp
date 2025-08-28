#include "Flight.h"
#include "Service.h"



Flight::Flight(const std::string& FlightNumber, const std::string& AirLine, const std::string& LandingTime)
{
	flightNumber = FlightNumber;
	airLine = AirLine;
	landignTime = LandingTime;


}

// Get Methods 
const std::string& Flight::getFlightNumber() const { return flightNumber; }
const std::string& Flight::getAirLine() const { return airLine; }
const std::string& Flight::getLandingTime() const { return landignTime; }
//Task Getters
const std::unordered_set<Service> Flight::getDemandingServices() const
{
	return demandingServices;
}
const std::unordered_set<FuelTasks> Flight::getFuelTasks() const
{
	return fuelTasks;

}
const std::unordered_set<LuggageTasks> Flight::getLuggageTasks() const
{
	return luggageTasks;
}
const std::unordered_set<CleaningTasks> Flight::getCleaningTasks() const
{
	return cleaningTasks;
}


// Set Methods
void Flight::setFlightNumber(const std::string& newFlightNumber) { flightNumber = newFlightNumber; }
void Flight::setAirLine(const std::string& newAirLine) { airLine = newAirLine; }
void Flight::setLandingTime(const std::string& newLandingTime) { landignTime = newLandingTime; }



// --- add ---
 void Flight::addDemandingServices(CleaningTasks t)  
{
	// sr’yi param olarak alsak da güvenli olan type’tan seti seçmek:
	demandingServices.insert(Cleaning);
	cleaningTasks.insert(t);
}

 void Flight::addDemandingServices(FuelTasks t)   
{
	demandingServices.insert(Service::Fuel);
	fuelTasks.insert(t);
}

 void Flight::addDemandingServices(LuggageTasks t) 
{
	demandingServices.insert(Service::Luggage);
	luggageTasks.insert(t);
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






