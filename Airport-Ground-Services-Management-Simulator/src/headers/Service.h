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
	Cleaning,   //1
	Fuel,		//2
	NoneService		//3


};

enum FuelTasks
{
	RefuelPlane,   //0
	RefuelTank,    //1
	TransportFuel, //2
	NoneFuel           //3
};

enum LuggageTasks
{
	LoadLuggage,       //0
	UnloadLuggage,	   //1
	TransportLuggage,  //2
	NoneLuggage			   //3

};

enum CleaningTasks
{
	Daily,   //0
	Weekly,  //1
	Monthly, //2
	Yearly,  //3
	NoneCleaning	 //4





};