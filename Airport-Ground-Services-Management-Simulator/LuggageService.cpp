#include "LuggageService.h"



LuggageService::LuggageService(std::map<int, std::string> staffList, int staffs)
	: GroundService(std::move(staffList), staffs)
{

}

const int& LuggageService::getStaffs()
{
	return staffs;
}

const std::string& LuggageService::getStaffNames(int staffNumber)
{
	return staffList.at(staffNumber);
}

//setters
void LuggageService::setStafs(int StaffNumber)
{
	staffs = StaffNumber;

}

void LuggageService::addStaffName(std::string& name, int staffNumber)
{
	staffList[staffNumber] = name;
}

void LuggageService::removeStaffName(int staffNumber)
{
	staffList.erase(staffNumber);
}
