#include <iostream>
#include <string>
#include "Flight.h"
using namespace std;





	Flight::Flight(string& FlightNumber, string& AirLine, string& LandingTime)
	{
		flightNumber = FlightNumber;
		airLine = AirLine;
		landignTime = LandingTime;

	}

		// Get Methods 
	string& Flight::getFlightNumber() { return flightNumber; }
	string& Flight::getAirLine() { return airLine; }
	string& Flight::getLandingTime() { return landignTime; }

		// Set Methods
	void Flight::setFlightNumber(string& newFlightNumber) { flightNumber = newFlightNumber; }
	void Flight::setAirLine(string& newAirLine) { airLine = newAirLine; }
	void Flight::setLandingTime(string& newLandingTime) { landignTime = newLandingTime; }
	