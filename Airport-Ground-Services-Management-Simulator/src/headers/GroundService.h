#pragma once

#include <string>
#include <map>


class GroundService
{

public:

	GroundService(std::map<int, std::string> staffList, int staffs);

	~GroundService() = default;

protected:
	std::map<int, std::string> staffList;
	int staffs = 0;





};