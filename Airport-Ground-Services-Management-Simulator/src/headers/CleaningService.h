#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "GroundService.h"
#include "Service.h"




class CleaningService :public GroundService
{
public:
	// Importance situation enum for emergency cleaning
	enum Importance {
		Critical,    // 0
		Threat,  // 1
		Emergency,  // 2
		Medium,  // 3
		Low    //4
	};

	CleaningService(std::map<int, std::string> staffList, int staffs);



	int EmergencyCleaning(const std::string& flightNumber, Importance importance);


	//Getters
	int getStaffs();
	const std::string& getStaffNames(int staffNumber);
	int getCleaningTime();


	//Setters
	void setStaffs(int StaffNumber);
	void addStaffName(const std::string& name, int staffNumber);
	void removeStaffName(int staffNumber);
	void setCleaningTime(int cleaningTime);




private:


	int cleaningTime = 0;





};



