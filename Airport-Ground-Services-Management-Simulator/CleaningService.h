#pragma once
#include "GroundService.h"
#include <iostream>
#include <vector>
#include <string>
class CleaningService :public GroundService
{
public:
	CleaningService();

	void DailyCleaning(const std::string& flightNumber);
	

	void MonthlyCleaning(const std::string& flightNumber);
	

	void YearlyCleaning(const std::string& flightNumber);
	

	int EmergencyCleaning(const std::string& flightNumber, int situationImportance);  //1-most 5-Less


	//Getters
	const int& getStaffs();
	const std::string& getStaffNames();
	const int& getCleaningTime();
	

	//Setters
	void setStafs(int StaffNumber);
	
	void addStaffName(std::string& name);

	void removeStaffName(std::string& name);

	void setCleaningTime(int cleaningTime);



	
private:

	int staffs=0;

	std::vector<std::string> staffNames;

	int cleaningTime=0;





};



