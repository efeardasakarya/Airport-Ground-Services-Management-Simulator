#pragma once
#include <map>
#include <string>
#include <thread>
#include <chrono>

// İmplementations for forward declaration
class Flight;
class GlobalLogger;
class ServiceHandler;
class LandingHandler;
class TakeoffHandler;

class ThreadHandler {
public:
    static ThreadHandler* getInstance();

    void landingThreadHandler(std::map<std::string, Flight>& flightRecords);
    void takeoffThreadHandler();

private:
    ThreadHandler();
    ~ThreadHandler();

    ThreadHandler(const ThreadHandler&) = delete;
    ThreadHandler& operator=(const ThreadHandler&) = delete;

    GlobalLogger* logger = nullptr;
    ServiceHandler* serviceHandler = nullptr;

    LandingHandler* landingHandler;
    TakeoffHandler* takeoffHandler;
};
