#pragma once
#include "Flight.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <map>


class FlightRecordsManager
{


private:
	std::map< std::string ,Flight > flights;

	std::ifstream loadFile(const std::string& fileName);

	void createFlightObjects(std::ifstream& file, std::map<std::string , Flight>& flights);

	void printFlights(const std::map<std::string,Flight>& flights);

	static inline void trimCR(std::string& line);

	bool checkFile(const std::string& fileName);

	
	

public:

FlightRecordsManager();


~FlightRecordsManager();    // Program sona geldi�inde otomatik olarak �al���r

void InitializeFlightRecordsManager(const std::string& fileName);

};