#pragma once
#include "GroundService.h"
#include <iostream>
#include <vector>
#include <string>

enum CleaningTasks
{
	Daily,
	Weekly,
	Monthly,
	Yearly,
	





};


class CleaningService :public GroundService
{
public:

	enum Importance {
		Critical,    // 0
		Threat,  // 1
		Emergency,  // 2
		Medium,  // 3
		Low    //4
	};

	CleaningService(std::map<int, std::string> staffList, int staffs);

	

	int EmergencyCleaning(const std::string& flightNumber, Importance imp);  


	//Getters
	const int& getStaffs();
	std::string& getStaffNames(int staffNumber);
	const int& getCleaningTime();
	

	//Setters
	void setStafs(int StaffNumber);
	void addStaffName(std::string& name , int staffNumber);
	void removeStaffName(int staffNumber);
	void setCleaningTime(int cleaningTime);

	CleaningTasks cleaningCrewTask(int crewID)
	{
		if (crewID < 3)
		{
			return Daily;
		}

		else if (crewID < 5)
		{
			return Weekly;
		}
		else if (crewID < 8)
		{
			return Monthly;
		}
		else 
		{
			return Yearly;
		}


	}






private:

	
	int cleaningTime=0;





};



