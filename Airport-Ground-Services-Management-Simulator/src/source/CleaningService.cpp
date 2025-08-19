#include "CleaningService.h"

CleaningService::CleaningService(std::map<int, std::string> staffList, int staffs) 
	: GroundService(std::move(staffList), staffs)
{
	
}

void CleaningService::DailyCleaning(const std::string& flightNumber)
{
	std::cout << "Daily procedure is running"<<'\n';
}

void CleaningService::MonthlyCleaning(const std::string& flightNumber)
{
	std::cout << "Monthly procedure is running" << '\n';
}

void CleaningService::YearlyCleaning(const std::string& flightNumber)
{
	std::cout << "Yearly procedure is running" << '\n';
}

int CleaningService::EmergencyCleaning(const std::string& flightNumber , int situationImportance )  //1-most 5-Less
{
	int cleanerStaffArrivalTime=0;

	switch (situationImportance)
	{
	case 1:
		cleanerStaffArrivalTime = 10;
		break;
	case 2:
		cleanerStaffArrivalTime = 15;
		break;
	case 3:
		cleanerStaffArrivalTime = 20;
		break;
	case 4:
		cleanerStaffArrivalTime = 30;
		break;
	case 5:
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