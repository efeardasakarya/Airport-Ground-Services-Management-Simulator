#include "Flight.h"
#include <iostream>
#include <string>


	Flight::Flight(std::string& FlightNumber, std::string& AirLine, std::string& LandingTime)
	{
		flightNumber = FlightNumber;
		airLine = AirLine;
		landignTime = LandingTime;

	}

		// Get Methods 
	 std::string Flight::getFlightNumber() { return flightNumber; }
	 std::string Flight::getAirLine() { return airLine; }
	 std::string Flight::getLandingTime() { return landignTime; }

		// Set Methods
	void Flight::setFlightNumber(std::string& newFlightNumber) { flightNumber = newFlightNumber; }
	void Flight::setAirLine(std::string& newAirLine) { airLine = newAirLine; }
	void Flight::setLandingTime(std::string& newLandingTime) { landignTime = newLandingTime; }
	