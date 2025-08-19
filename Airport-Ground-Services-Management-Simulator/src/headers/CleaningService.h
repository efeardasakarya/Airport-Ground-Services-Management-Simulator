#pragma once
#include "GroundService.h"
#include <iostream>
#include <vector>
#include <string>
class CleaningService :public GroundService
{
public:
	CleaningService(std::map<int, std::string> staffList, int staffs);

	void DailyCleaning(const std::string& flightNumber);
	

	void MonthlyCleaning(const std::string& flightNumber);
	

	void YearlyCleaning(const std::string& flightNumber);
	

	int EmergencyCleaning(const std::string& flightNumber, int situationImportance);  //1-most 5-Less


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



