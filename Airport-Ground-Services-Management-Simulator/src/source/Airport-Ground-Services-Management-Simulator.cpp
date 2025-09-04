#include <map>
#include <string>
#include <thread>

#include "ThreadHandler.h"
#include "Flight.h"
#include "GlobalLogger.h"
#include "FlightRecordsManager.h"

int main() {

    GlobalLogger::getInstance()->important("Simulator starting...");

    FlightRecordsManager flighRecordManager;


    // Register file. Read all flight infos and hold in a map indexin by Flight Numbers.
    std::map<std::string, Flight> flightRecords = flighRecordManager.InitializeFlightRecordsManager("data/flight_program.csv");


    // EXAMPLE for adding flights after file reading
    
    // flightRecords.emplace("TK101", Flight{"TK101","THY","18:30"});
    // flightRecords.emplace("TK202", Flight{"TK202","THY","18:45"});
    // flightRecords.emplace("PC303", Flight{"PC303","Pegasus","19:00"});
    if (!flightRecords.empty())
    {


        ThreadHandler* threadHandler = ThreadHandler::getInstance();

        // İki yönetici thread: biri iniş işleri atar, diğeri yerdeki kuyruktan tüketir
        std::thread landingThread([&] { threadHandler->landingThreadHandler(flightRecords); });
        std::thread takeoffThread([&] { threadHandler->takeoffThreadHandler(); });

        landingThread.join();
        takeoffThread.join();
        return 0;
    }
    else
    {
        return 0;
    }
}
