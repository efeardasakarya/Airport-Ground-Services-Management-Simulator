#pragma once
#include "GroundService.h"
#include "Service.h"




class LuggageService :public GroundService
{
public:

	LuggageService(std::map<int, std::string> staffList, int staffs);

	//Getters
	int getStaffs();
	const std::string& getStaffNames(int staffNumber);

	//Setters
	void setStaffs(int StaffNumber);
	void addStaffName(const std::string& name, int staffNumber);
	void removeStaffName(int staffNumber);


	void seperateLuggagesToPlane(float luggageWeight);

	void seperateLuggagesFromPlane(float luggageWeight);

	bool checkBaggage();
	
	

private:

	int lightLuggageCounter=0;
	int midLuggageCounter=0;
	int heavyLuggageCounter=0;


};

