// Airport-Ground-Services-Management-Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//General
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


//Private
#include "Flight.h"

using namespace std;


int main()
{


    ifstream file("flight_program.csv");
    vector<Flight> flights;
    string line;
    
    //Flight Class variables
    string flightNumber;
    string airLine;
    string landingTime;



    if (!file.is_open())
    {
        cout << "File can not opened ";
        return 1;
    }

    //Read first line and skip. 
    getline(file, line);

    //Continue from second line

    while (getline(file,line))
    {
        stringstream flightInfos(line);
        

        getline(flightInfos, flightNumber, ',');
        getline(flightInfos, airLine, ',');
        getline(flightInfos, landingTime, ',');

        flights.emplace_back(flightNumber, airLine, landingTime);

    }
    
    for(auto f : flights )
    {
        cout << f.getAirLine() << "|";
        cout << f.getFlightNumber() << "|";
        cout << f.getLandingTime() << "|";
        cout << endl;

    }

   
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
