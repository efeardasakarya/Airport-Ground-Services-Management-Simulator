#include "CleaningService.h"

CleaningService::CleaningService()
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

const std::string& CleaningService::getStaffNames()
{
	for (std::string name : staffNames)
	{
		std::cout << name << '\n';
	}
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

void CleaningService::addStaffName(std::string& name)
	{
		staffNames.push_back(name);
	}

void CleaningService::removeStaffName(std::string& name)
	{
		for (auto temp : staffNames)
		{
			auto iterator = std::find(staffNames.begin(), staffNames.end(), name);
			staffNames.erase(iterator);

		}
	}

void CleaningService::setCleaningTime(int cleaningTime)
{
	this->cleaningTime = cleaningTime;
}