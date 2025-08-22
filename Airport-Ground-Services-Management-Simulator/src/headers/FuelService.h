#pragma once

#include "GroundService.h"
#include "Service.h"






class FuelService :public GroundService
{
public:

	FuelService(std::map<int, std::string> staffList, int staffs);

	//Getters
	const int& getStaffs();
	const std::string& getStaffNames(int staffNumber);
		
	//Setters
	void setStafs(int StaffNumber);
	void addStaffName(std::string& name, int staffNumber);
	void removeStaffName(int staffNumber);
	
	void fuelSupply(float fuelAmount);
	void transferFuel(float fuelAmount , const std::string& flightNumber);


	

private:
	float currentFuelAmount = 0;
};

