#pragma once

#include "CleaningService.h"
#include "FuelService.h"
#include "LuggageService.h"
#include <map>
#include <mutex>
#include <string>


enum Service
{
	Luggage,    //0
	Cleaning,  //1
	Fuel,		//2
	None


};

enum FuelTasks
{
	RefuelPlane, //0
	RefuelTank,  //1
	TransportFuel //2

};

enum LuggageTasks
{
	LoadLuggage,  //0
	UnloadLuggage, //1
	TransportLuggage  //2

};

enum CleaningTasks
{
	Daily,   //0
	Weekly,  //1
	Monthly, //2
	Yearly,  //3






};