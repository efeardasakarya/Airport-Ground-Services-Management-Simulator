#include "ThreadHandler.h"
#include "LandingHandler.h"
#include "TakeoffHandler.h"
#include "ServiceHandler.h"
#include "GlobalLogger.h"
#include "Flight.h"


// Constructor
ThreadHandler::ThreadHandler() 
{
    logger = GlobalLogger::getInstance();
    serviceHandler = ServiceHandler::getInstance();
    landingHandler = new LandingHandler();
    takeoffHandler = new TakeoffHandler();
}

// Destructor
ThreadHandler::~ThreadHandler() 
{
    delete landingHandler;
    delete takeoffHandler;
}

// Meyers singleton pattern
// Hold instance as local variable for safety
ThreadHandler* ThreadHandler::getInstance() 
{
    static ThreadHandler inst;
    return &inst;
}

void ThreadHandler::landingThreadHandler(std::map<std::string, Flight>& flightRecords) 
{
    while (true) 
    {
        
        for (int i = 0; i < 2; ++i) 
        {
            if (/* Check file for any valid flight */landingHandler->hasWork(flightRecords) > 0 && /* Check for available runways*/ serviceHandler->tryBookRunway())
            {
                /*
                Can't join detached thread and continue execution. When the job finished std::terminate execute.
                this = Get ThreadHandler as pointer. If ThreadHandler destroys -> Undefined Behaviour
                */
                std::thread([this, &flightRecords] { landingHandler->landingProcess(flightRecords); }).detach();
            }
            else 
            {
                /*
                Leave the loop if can't find any flight or available runways
                */
                break;
            }
        }
        // Make loop every 0.2 seconds. Little break for prevent infinite loop.
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void ThreadHandler::takeoffThreadHandler() 
{
    // Check queue for every 0.05 seconds. If has any grounded flight takeoffProcess start.
    while (true) 
    {
        takeoffHandler->takeoffProcess();
        
        // Prevent infinite loops
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
