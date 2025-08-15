#pragma once
#include "Flight.h"
#include <vector>


class FlightRecordsManager
{


private:
	std::vector<Flight> flights;


public:

FlightRecordsManager();


~FlightRecordsManager() = default;    // Program sona geldiðinde otomatik olarak çalýþýr

std::ifstream loadFile(std::string fileName);

void createFlightObjects(std::ifstream& file, std::vector<Flight>& flights);

void printFlights(const std::vector<Flight>& Flights);

static inline void trimCR(std::string& line);

};