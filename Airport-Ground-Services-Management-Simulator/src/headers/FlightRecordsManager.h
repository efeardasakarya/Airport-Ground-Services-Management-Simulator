#pragma once
#include "Flight.h"
#include <vector>
#include <sstream>
#include <fstream>


class FlightRecordsManager
{


private:
	std::vector<Flight> flights;

	std::ifstream loadFile(const std::string& fileName);

	void createFlightObjects(std::ifstream& file, std::vector<Flight>& flights);

	void printFlights(const std::vector<Flight>& Flights);

	static inline void trimCR(std::string& line);

	bool checkFile(const std::string& fileName);

	
	

public:

FlightRecordsManager();


~FlightRecordsManager();    // Program sona geldi�inde otomatik olarak �al���r

void InitializeFlightRecordsManager(const std::string& fileName);

};