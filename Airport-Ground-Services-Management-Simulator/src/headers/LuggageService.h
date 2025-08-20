#pragma once
#include "GroundService.h"

enum LuggageTasks
{
	LoadLuggage,
	UnloadLuggage,
	TransportLuggage

};



class LuggageService :public GroundService
{
public:

	LuggageService(std::map<int, std::string> staffList, int staffs);

	//Getters
	const int& getStaffs();
	const std::string& getStaffNames(int staffNumber);

	//Setters
	void setStafs(int StaffNumber);
	void addStaffName(std::string& name, int staffNumber);
	void removeStaffName(int staffNumber);


	void seperateLuggagesToPlane(float luggageWeight);

	void seperateLuggagesFromPlane(float luggageWeight);

	bool checkBaggage();
	
	LuggageTasks luggageCrewTask(int crewID);

private:

	int lightLuggageCounter=0;
	int midLuggageCounter=0;
	int heavyLuggageCounter=0;


};

