#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include "Service.h"



class Flight
{

private:
	std::string flightNumber;
	std::string airLine;
	std::string landignTime;

	std::unordered_set<Service>demandingServices;
	std::unordered_set<FuelTasks>fuelTasks;
	std::unordered_set<LuggageTasks>luggageTasks;
	std::unordered_set<CleaningTasks>cleaningTasks;



public:

	Flight(const std::string& FlightNumber, const std::string& AirLine, const std::string& LandingTime);


	~Flight() = default;    // Program sona geldiðinde otomatik olarak çalýþýr




	// Get Methods 
	const std::string& getFlightNumber() const;
	const std::string& getAirLine() const;
	const std::string& getLandingTime() const;

	//Task getters
	const std::unordered_set<Service> getDemandingServices() const;
	const std::unordered_set<FuelTasks> getFuelTasks() const;
	const std::unordered_set<LuggageTasks> getLuggageTasks() const;
	const std::unordered_set<CleaningTasks> getCleaningTasks() const;

	// Set Methods
	void setFlightNumber(const std::string& newFlightNumber);
	void setAirLine(const std::string& newAirLine);
	void setLandingTime(const std::string& newLandingTime);



	void addDemandingServices(CleaningTasks t);
	void addDemandingServices(FuelTasks t);
	void addDemandingServices(LuggageTasks t);

	void removeDemandingServices(CleaningTasks t);
	void removeDemandingServices(FuelTasks t);
	void removeDemandingServices(LuggageTasks t);





protected:






};
