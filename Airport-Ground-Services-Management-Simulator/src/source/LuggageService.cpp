#include "LuggageService.h"


//
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

void LuggageService::seperateLuggagesToPlane(float luggageWeight)
{
	if (luggageWeight < 3.5)
	{
		lightLuggageCounter++;
	}

	else if (luggageWeight > 9)
	{
		midLuggageCounter++;
	}

	else
	{
		heavyLuggageCounter++;
	}


}

void LuggageService::seperateLuggagesFromPlane(float luggageWeight)
{
	if (luggageWeight < 3.5)
	{
		lightLuggageCounter++;
	}

	else if (luggageWeight > 9)
	{
		midLuggageCounter++;
	}

	else
	{
		heavyLuggageCounter++;
	}
}

bool LuggageService::checkBaggage()
{
	{
		return (lightLuggageCounter == 0 && midLuggageCounter == 0 && heavyLuggageCounter == 0);

	}
}

LuggageTasks LuggageService::luggageCrewTask(int crewID)
{
	if (crewID < 4)
	{
		return LoadLuggage;
	}


	else if (crewID > 6)
	{
		return UnloadLuggage;
	}

	else
	{
		return TransportLuggage;
	}


}