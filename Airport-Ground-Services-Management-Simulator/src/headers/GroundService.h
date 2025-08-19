#pragma once

#include <string>
#include <map>


class GroundService
{
protected:
	std::map<int, std::string> staffList;
	int staffs = 0;

public:

	GroundService(std::map<int, std::string> staffList, int staffs = 0 );

	~GroundService()  = default;



};