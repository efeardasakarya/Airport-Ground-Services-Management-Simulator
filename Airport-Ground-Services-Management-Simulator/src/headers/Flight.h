#pragma once
#include <iostream>
#include <string>



class Flight
{
private:
	std::string flightNumber;
	std::string airLine;
	std::string landignTime;


public:

	Flight(std::string& FlightNumber, std::string& AirLine, std::string& LandingTime);


		~Flight()=default;    // Program sona geldi�inde otomatik olarak �al���r
	



	// Get Methods 
	 std::string getFlightNumber();
	 std::string getAirLine();
	 std::string getLandingTime();

	// Set Methods
	void setFlightNumber(std::string& newFlightNumber);
	void setAirLine(std::string& newAirLine);
	void setLandingTime(std::string& newLandingTime);






protected:






};
