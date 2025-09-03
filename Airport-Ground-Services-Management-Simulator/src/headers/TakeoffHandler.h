#pragma once

#include <memory>

// Fwd decls
class GlobalLogger;
class ServiceHandler;
class Flight;

class TakeoffHandler {
public:
    
    TakeoffHandler();
    ~TakeoffHandler();

    // Pick a flight from groundedFlights queue , process the services , takeoff the flight and release the runway
    void takeoffProcess();

private:
    // Give a duration for complete service
    static int durationForLuggageTask(int taskEnum);   // saniye
    static int durationForCleaningTask(int taskEnum);  // saniye
    static int durationForFuelTask(int taskEnum);      // saniye

    // Process the service
    void runLuggageTasks(const std::shared_ptr<Flight>& flight);
    void runCleaningTasks(const std::shared_ptr<Flight>& flight);
    void runFuelTasks(const std::shared_ptr<Flight>& flight);

private:
    GlobalLogger* logger = nullptr ;
    ServiceHandler* serviceHandler = nullptr;
};
