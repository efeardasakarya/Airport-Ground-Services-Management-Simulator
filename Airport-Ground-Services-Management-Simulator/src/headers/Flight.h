#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Service.h"
#include "SimulationTime.h"



class Flight
{

private:
	std::string flightNumber;
	std::string airLine;
	std::string landingTime;

	std::unordered_set<Service>demandingServices;
	std::unordered_map<FuelTasks, int>fuelTasks;
	std::unordered_map<LuggageTasks , int>luggageTasks;
	std::unordered_map<CleaningTasks, int>cleaningTasks;

	SimulationTime* simulationTime = nullptr;

public:

	Flight(const std::string& FlightNumber, const std::string& AirLine, const std::string& LandingTime);


	~Flight() = default;    // Automatically runs when program finished




	// Get Methods 
	const std::string& getFlightNumber() const;
	const std::string& getAirLine() const;
	const std::string& getLandingTime() const;

	//Task getters
	const std::unordered_set<Service> getDemandingServices() const;
	const std::unordered_map<FuelTasks , int> getFuelTasks() const;
	const std::unordered_map<LuggageTasks , int> getLuggageTasks() const;
	const std::unordered_map<CleaningTasks , int > getCleaningTasks() const;

	// Set Methods
	void setFlightNumber(const std::string& newFlightNumber);
	void setAirLine(const std::string& newAirLine);
	void setLandingTime(const std::string& newLandingTime);


	// Override functions for addDemandingServices and removeDemandingServices. Called by task type (clenaing , fuel , luggage)
	void addDemandingServices(CleaningTasks t);
	void addDemandingServices(FuelTasks t);
	void addDemandingServices(LuggageTasks t);

	void removeDemandingServices(CleaningTasks t);
	void removeDemandingServices(FuelTasks t);
	void removeDemandingServices(LuggageTasks t);

	int durationForLuggageTask(LuggageTasks task)
	{
		// Get Luggage task by index. Look Service.h for indexes
		
		// Get process duration by task
		switch (task)
		{
		case LuggageTasks::LoadLuggage:
			return 6;
		case LuggageTasks::UnloadLuggage:
			return 4;
		case LuggageTasks::TransportLuggage:
			return 5;
		default:
			return 0;
		}
	}
	int durationForCleaningTask(CleaningTasks task)
	{   
		switch (task) 
		{
		case CleaningTasks::Daily:
			return 2;
		case CleaningTasks::Weekly:
			return 3;
		case CleaningTasks::Monthly:
			return 4;
		case CleaningTasks::Yearly:
			return 5;
		default:
			return 0;
		}
	}
	int durationForFuelTask(FuelTasks task)
	{
		switch (task)
		{
		case FuelTasks::RefuelPlane:
			return 6;
		case FuelTasks::RefuelTank:
			return 5;
		case FuelTasks::TransportFuel:
			return 4;
		default:
			return 1;
		}
	}

protected:


};
