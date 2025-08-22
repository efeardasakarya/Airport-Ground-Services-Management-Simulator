#pragma once

#include <sstream>
#include <fstream>
#include <map>
#include <memory>

#include "Flight.h"



class FlightRecordsManager
{


private:
	std::map< std::string ,Flight > flights;

	std::ifstream loadFile(const std::string& fileName);

	std::map<std::string, Flight>& createFlightObjects(std::ifstream& file, std::map<std::string , Flight>& flights);

	void printFlights(const std::map<std::string,Flight>& flights);

	static inline void trimCR(std::string& line);

	bool checkFile(const std::string& fileName);

	
	

public:

FlightRecordsManager();


~FlightRecordsManager();    // Program sona geldi�inde otomatik olarak �al���r

std::map<std::string, Flight>& InitializeFlightRecordsManager(const std::string& fileName);

};