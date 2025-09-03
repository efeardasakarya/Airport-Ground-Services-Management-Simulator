#pragma once
#include <map>
#include <string>
#include <optional>
#include <mutex>

// İmplementations for forward declaration
class Flight;
class GlobalLogger;
class ServiceHandler;

class LandingHandler {
public:
    LandingHandler();
    ~LandingHandler();

    void landingProcess(std::map<std::string, Flight>& flightRecords);
    int  hasWork(std::map<std::string, Flight>& flightRecords);

private:
    static int randomNumberGenerator(int minimum, int maximum); // EXAMPLE randomNumberGenerator(1,10) -> returns value between 1 and 10

    // Prevent data race on flightRecords
    std::mutex refLock;

    GlobalLogger* logger = nullptr;
    ServiceHandler* serviceHandler = nullptr;
};
