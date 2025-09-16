#pragma once
#include <memory>
#include <list>
#include <thread>
#include <future>
#include <mutex>


// Forward Declaration
class GlobalLogger;
class ServiceHandler;
class Flight;

class TakeoffHandler 
{

public:

	TakeoffHandler();
	~TakeoffHandler();
	// Pick a flight from groundedFlights queue , process the services , takeoff the flight and release the runway
	void takeoffProcess();
	void checkThreads(bool finalize = false);

private:

	// Process the service
	void runLuggageTasks(const std::shared_ptr<Flight>& flight);
	void runCleaningTasks(const std::shared_ptr<Flight>& flight);
	void runFuelTasks(const std::shared_ptr<Flight>& flight);

	GlobalLogger* logger = nullptr;
	ServiceHandler* serviceHandler = nullptr;
	
	std::vector<std::thread> threads;
	std::vector<std::shared_ptr<std::atomic_bool>> doneThreads;
	std::mutex threadsMutex;
};
