#include <iostream>
#include <string>
using namespace std;

class Flight
{
private:
	string flightNumber;
	string airLine;
	string landignTime;


public:

		// Get Methods 
	string getFlightNumber() { return flightNumber; }
	string getAirLine() { return airLine; }
	string getLandingTime() { return landignTime; }

		// Set Methods
	void setFlightNumber(string newFlightNumber) { flightNumber = newFlightNumber; }
	void setAirLine(string newAirLine) { airLine = newAirLine; }
	void setLandingTime(string newLandingTime) { landignTime = newLandingTime; }






protected:
	

	



};