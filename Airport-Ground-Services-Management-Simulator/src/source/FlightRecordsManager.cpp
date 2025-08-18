
#include "FlightRecordsManager.h"
#include <iostream>
#include <string>
#include <stdexcept> // runtime_error
#include <filesystem> // C++17
#include "GlobalLogger.h"




	


	FlightRecordsManager::FlightRecordsManager()
	{

	};



    inline void FlightRecordsManager::trimCR(std::string& line)
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
    }



    FlightRecordsManager::~FlightRecordsManager() = default;
    

    bool FlightRecordsManager::checkFile(const std::string& fileName)
    {

        
        return std::filesystem::exists(fileName);


    } // Checking gucntion before load 
    

 
	std::ifstream FlightRecordsManager::loadFile(const std::string& fileName)
	{
        try
        {
            std::ifstream file;

               file.exceptions(std::ifstream::badbit);

               file.open(fileName);

               return file;

        }

        catch (const std::ios_base::failure& fail)
        {
            //  Add logging here
           
            return std::ifstream(); // return null ifstream reference
        }

                  
                     
   
	}

   

    void FlightRecordsManager::createFlightObjects(std::ifstream& file, std::vector<Flight>& flights)
    {
        //if first line is empty kill the function
        std::string line;
        if (!std::getline(file, line)) return;

        //Local Variables
        std::string flightNumber;
        std::string airLine;
        std::string landingTime;

        std::istringstream flightInfos; // We create istringstream object in here just once. Don't create in loop
        // That's better for performance

        //Continue from second line
        while (std::getline(file, line))
        {
            if (line.empty()) continue; // if line is empty skip it


            flightInfos.clear();     //delete previous line from istream and give another line.
            flightInfos.str(line);   //So you don't have to create istringstream object again and again
            // this is not a problem for little size files but for bigger projects 
           //can cause performance problems

            


            std::getline(flightInfos, flightNumber, ',');
            std::getline(flightInfos, airLine, ',');
            std::getline(flightInfos, landingTime, ',');

            trimCR(flightNumber);
            trimCR(airLine);
            trimCR(landingTime);


            if (flightNumber.empty() || airLine.empty() || landingTime.empty())
                continue;

            // emplace back create the object and add to the vector. Better performance than push.back()
            flights.emplace_back( flightNumber, airLine, landingTime );

        }

    }



    void FlightRecordsManager::printFlights(const std::vector<Flight>& Flights)
    {
        for (auto f : Flights)
        {
            std::cout << f.getAirLine() << "|";
            std::cout << f.getFlightNumber() << "|";
            std::cout << f.getLandingTime() << '\n';


        }
    }

	

    void FlightRecordsManager::InitializeFlightRecordsManager(const std::string& fileName)
    {
        
        

        if (checkFile(fileName))
        {
            std::ifstream flightRecords = loadFile(fileName);

            if (flightRecords.is_open())
            {
                createFlightObjects(flightRecords, flights);

                printFlights(flights);
            }


        }
        else
        {

            std::filesystem::path relpath(fileName);
            std::filesystem::path absPath = std::filesystem::absolute(relpath);

            //Add logger here
            
            }
                  
                 
    }
        
       


        

    

