#include "FuelService.h"

FuelService::FuelService(std::map<int, std::string> staffList, int staffs) : GroundService(std::move(staffList), staffs)
{

}


//getters
int FuelService::getStaffs()
{
	return staffs;
}

const std::string& FuelService::getStaffNames(int staffNumber)
{
	return staffList.at(staffNumber);
}

//setters
void FuelService::setStaffs(int StaffNumber)
{
	staffs = StaffNumber;
	
}

void FuelService::addStaffName(const std::string& name, int staffNumber)
{
	staffList[staffNumber] = name;
}

void FuelService::removeStaffName(int staffNumber)
{
	staffList.erase(staffNumber);
}

void FuelService::fuelSupply(float fuelAmount)
{
	currentFuelAmount += fuelAmount;
}

void FuelService::transferFuel(float fuelAmount , const std::string& flightNumber)
{
	currentFuelAmount -= fuelAmount;
	
}


