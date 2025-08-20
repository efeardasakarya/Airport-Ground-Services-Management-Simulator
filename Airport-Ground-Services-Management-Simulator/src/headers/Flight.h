#pragma once
#include <iostream>
#include <string>
#include <memory>
enum Service
{
	Lugagge,    //0
	Clenaning,  //1
	Fuel,		//2
	None


};


class Flight
{
	




private:
	std::string flightNumber;
	std::string airLine;
	std::string landignTime;
	Service demandingService;



public:

	Flight(std::string& FlightNumber, std::string& AirLine, std::string& LandingTime);


		~Flight()=default;    // Program sona geldiðinde otomatik olarak çalýþýr
	



	// Get Methods 
	const std::string& getFlightNumber() const ;
	const std::string& getAirLine() const ;
	const std::string& getLandingTime() const;
	Service getDemandingService();

	// Set Methods
	void setFlightNumber(const std::string& newFlightNumber);
	void setAirLine(const std::string& newAirLine);
	void setLandingTime(const std::string& newLandingTime);
	void setDemandingService(const Service sr);





protected:






};
