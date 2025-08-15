
#include "FlightRecordsManager.h"
#include <iostream>
#include <string>
#include <stdexcept> // runtime_error

	


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
    
       
    
	std::ifstream FlightRecordsManager::loadFile(const std::string& fileName)
	{
        
      
            std::ifstream file(fileName);

            if (file.is_open())
            {
                std::cout << "File is valid" << std::endl;
                return file;
            }

            else {

                //Ýf file can not open. function returns null value
                return std::ifstream(); 
                
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
            flights.emplace_back(flightNumber, airLine, landingTime);

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

	

    void FlightRecordsManager::InitializeFlightRecordsManager(const std::string fileName)
    {
        std::ifstream flightRecords = loadFile(fileName);

        try
        {
            if (flightRecords.is_open())
            {
                createFlightObjects(flightRecords, flights);

                printFlights(flights);
            }
            else
            {
                throw std::runtime_error("File can not open. Please check the file path!");
            }
        }
        catch (const std::exception& e) // This exception provide error messages in runtime
        {
            std::cerr << "Hata: " << e.what() << std::endl;
        }


        

    }

