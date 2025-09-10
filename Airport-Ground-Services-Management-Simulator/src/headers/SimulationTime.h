#pragma once
#include <string>
#include <sstream>


class SimulationTime
{
public:

	SimulationTime() = default;

	~SimulationTime() = default;
	

	static SimulationTime* getInstance()
	{
		static SimulationTime inst;
		return &inst;

	}

	static constexpr int loopDuration = 1440;

	int clockMinute = 0;

	struct ClockTime {
		int hour{ 0 };
		int minute{ 0 };

		// Doğru yer: ClockTime içinde üye eşitlik
		constexpr bool operator==(const ClockTime& o) const noexcept {
			return hour == o.hour && minute == o.minute;
		}
	};

	// Get flight landing time and convert to minutes for compare in main function easily
	// For example : landing time 3.20 -> 200 minute. When the clock variable is 200 flight land.
	static int convertLandingTimeToMinute(const std::string& time);

	//Conver minutes to hour unit for std::cout or logger->info()
	ClockTime calculateTime(int counter) const ;


};

