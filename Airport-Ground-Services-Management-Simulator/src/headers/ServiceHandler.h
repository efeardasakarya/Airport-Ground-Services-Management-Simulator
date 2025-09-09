#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>

// Implement for enums
#include "Service.h"

// forward declaration
class Flight;
class GlobalLogger;

class ServiceHandler
{
public:
	static ServiceHandler* getInstance()
	{
		static ServiceHandler inst;
		return &inst;
	}

	// Runway Management
	bool tryBookRunway();       //Book a runway if available runway count is > 0. Decrease 1 available runway count. 
	void releaseRunway();       //Increase 1 available runway counter when the plane takesoff.    
	int  getAvailableRunwayCount() const;  // vaialble runway caount can't change inside the program. Only-read

	// Queue keep the grounded flights after landing for service adding (thread-safe)
	void enqueueGroundedFlight(std::shared_ptr<Flight> flight);
	std::shared_ptr<Flight> popGroundedFlight(); // Get the first element of the groundedFlights for add service.

	// Eski kodla uyumluluk için: input sırasında logger kilidi (isimini koruyorum)
	void serviceHandler(const std::shared_ptr<Flight>& flight); 

	

private:
	ServiceHandler();
	~ServiceHandler();

	ServiceHandler(const ServiceHandler&) = delete;
	ServiceHandler& operator=(const ServiceHandler&) = delete;


	// Task handlers for add/remove service to flight
	void luggageTaskHandler(Flight* landingFlight, bool adding);
	void cleaningTaskHandler(Flight* landingFlight, bool adding);
	void fuelTaskHandler(Flight* landingFlight, bool adding);


	// Runway counter (atomic & thread-safe)
	std::atomic<int> availableRunway{ 2 };

	// Mutex for data-race
	mutable std::mutex groundedMtx;
	std::mutex userInputMtx;

	std::condition_variable groundedCv;
	std::queue<std::shared_ptr<Flight>> groundedFlights;

	GlobalLogger* logger{ nullptr };
};
