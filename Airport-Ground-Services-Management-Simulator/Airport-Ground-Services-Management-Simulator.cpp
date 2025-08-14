// Airport-Ground-Services-Management-Simulator.cpp 

//General

#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>

//Private
#include "Flight.h"

static inline void trim_cr(std::string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}

void printFlights(const std::vector<Flight>& Flights)
{
    for (auto f : Flights)
    {
        std::cout << f.getAirLine() << "|";
        std::cout << f.getFlightNumber() << "|";
        std::cout << f.getLandingTime() << '\n';
        

    }
}

void createFlightObjects(std::ifstream& file, std::vector<Flight>& flights)
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
        while (getline(file, line))
        {
            if (line.empty()) continue; // line is empty skip it


            flightInfos.clear();     //delete previous line from istream and give another line.
            flightInfos.str(line);   //So you don't have to create istringstream object again and again
                                     // this is not a problem for little size files but for bigger projects 
                                    //can cause performance problems

            getline(flightInfos, flightNumber, ',');
            getline(flightInfos, airLine, ',');
            getline(flightInfos, landingTime, ',');

            
            trim_cr(flightNumber);
            trim_cr(airLine);        // Delete  '\r' on the end o the lines in windows
            trim_cr(landingTime);


                if (flightNumber.empty() || airLine.empty() || landingTime.empty())
        continue;

            // emplace back create the object and add to the vector. Better performance than push.back()
            flights.emplace_back(flightNumber, airLine,landingTime );

        }
    
}


int main()
{
    //Variables
    
        std::ifstream file("flight_program.csv");
        std::vector<Flight> flights;
        

    if (!file.is_open())
    {
        std::cout << "File can not opened ";
        return 1;
    }

    createFlightObjects(file,flights);
   
    printFlights(flights);
   
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
