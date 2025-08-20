#include "Flight.h"



	Flight::Flight(std::string& FlightNumber, std::string& AirLine, std::string& LandingTime)
	{
		flightNumber = FlightNumber;
		airLine = AirLine;
		landignTime = LandingTime;
		demandingService = None;

	}

		// Get Methods 
	const std::string& Flight::getFlightNumber() const { return flightNumber; }
	 const std::string& Flight::getAirLine() const { return airLine; }
	 const std::string& Flight::getLandingTime() const { return landignTime; }
	 Service Flight::getDemandingService() { return demandingService; }

		// Set Methods
	void Flight::setFlightNumber(const std::string& newFlightNumber) { flightNumber = newFlightNumber; }
	void Flight::setAirLine(const std::string& newAirLine) { airLine = newAirLine; }
	void Flight::setLandingTime(const std::string& newLandingTime) { landignTime = newLandingTime; }
	void Flight::setDemandingService(Service sr) { demandingService = sr; }