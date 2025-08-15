#pragma once
#include "Flight.h"
#include <vector>


class FlightRecordsManager
{


private:
	std::vector<Flight> flights;


public:

FlightRecordsManager();


~FlightRecordsManager() = default;    // Program sona geldi�inde otomatik olarak �al���r

std::ifstream loadFile(std::string fileName);

void createFlightObjects(std::ifstream& file, std::vector<Flight>& flights);

void printFlights(const std::vector<Flight>& Flights);

static inline void trimCR(std::string& line);

};