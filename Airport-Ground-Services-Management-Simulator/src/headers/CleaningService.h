#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "GroundService.h"
#include "Service.h"




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

	


private:

	
	int cleaningTime=0;





};



