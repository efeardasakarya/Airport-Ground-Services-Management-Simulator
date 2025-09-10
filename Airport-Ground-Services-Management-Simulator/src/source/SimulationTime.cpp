#include "SimulationTime.h"
#include <sstream>
#include <stdexcept>


int SimulationTime::convertLandingTimeToMinute(const std::string& time)
{
	int hour = 0;
	int minute = 0;
	char separator = 0;
	std::stringstream seperate(time);
	seperate >> hour >> separator >> minute;

	return (hour * 60) + minute;
}

//Conver minutes to hour unit for std::cout or logger->info()
SimulationTime::ClockTime SimulationTime::calculateTime(int counter) const
{

	return ClockTime(counter / 60, counter % 60);

}

