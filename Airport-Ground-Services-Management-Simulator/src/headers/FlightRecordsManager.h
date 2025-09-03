#pragma once

#include <sstream>
#include <fstream>
#include <map>
#include <memory>

#include "Flight.h"



class FlightRecordsManager
{


private:
	// Storage for flight recprds from flight_program.csv file
	std::map< std::string ,Flight > flights;

	std::ifstream loadFile(const std::string& fileName);

	std::map<std::string, Flight>& createFlightObjects(std::ifstream& file, std::map<std::string , Flight>& flights);

	void printFlights(const std::map<std::string,Flight>& flights);

	static inline void trimCR(std::string& line);

	bool checkFile(const std::string& fileName);

	
	

public:

FlightRecordsManager();


~FlightRecordsManager();    // Program sona geldiğinde otomatik olarak çalışır

std::map<std::string, Flight>& InitializeFlightRecordsManager(const std::string& fileName);

};