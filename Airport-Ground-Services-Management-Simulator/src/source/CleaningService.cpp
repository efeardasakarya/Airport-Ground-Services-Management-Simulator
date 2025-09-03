#include "CleaningService.h"

#include <iostream>


CleaningService::CleaningService(std::map<int, std::string> staffList, int staffs) : GroundService(std::move(staffList), staffs)
{
	
}

int CleaningService::EmergencyCleaning(const std::string& flightNumber , Importance importance)  // Importance enum is in the CleaningService.h
{
	int cleanerStaffArrivalTime=0;

	switch (importance)
	{
	case Critical:
		cleanerStaffArrivalTime = 10;
		break;
	case Emergency:
		cleanerStaffArrivalTime = 15;
		break;
	case Threat:
		cleanerStaffArrivalTime = 20;
		break;
	case Medium:
		cleanerStaffArrivalTime = 30;
		break;
	case Low:
		cleanerStaffArrivalTime = 40;
		break;

	}
	return cleanerStaffArrivalTime;
	
}




//getters
const int& CleaningService::getStaffs()
{
	return staffs;
}

std::string& CleaningService::getStaffNames(int staffNumber)
{
	return staffList.at(staffNumber);
}

const int& CleaningService::getCleaningTime()
{
	return cleaningTime;
}





//Setters
void CleaningService::setStafs(int StaffNumber)
{
	staffs = StaffNumber;
}

void CleaningService::addStaffName(std::string& name , int staffNumber)
	{
	staffList[staffNumber] = name;
	}

void CleaningService::removeStaffName(int staffNumber)
	{
	staffList.erase(staffNumber);
	}

void CleaningService::setCleaningTime(int cleaningTime)
{
	this->cleaningTime = cleaningTime;
}