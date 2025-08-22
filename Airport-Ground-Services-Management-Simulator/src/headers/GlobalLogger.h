#pragma once

#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/async.h"


class GlobalLogger
{
private:
	static GlobalLogger* instance;
	std::shared_ptr<spdlog::logger> asyncLogger;

	GlobalLogger(); // Singleton constructor must be private against the copy from other classes

	~GlobalLogger(); 

	
	
	
	
	// in the future process print and create functions going to be merged.

public:
	GlobalLogger(const GlobalLogger&) = delete;
	GlobalLogger& operator=(const GlobalLogger&) = delete;

	static GlobalLogger* getInstance();
	


	void asyncMultiSink();

	void printInfo(const std::string& InfoMessage);

	void printError(const std::string& ErrorMessage);

			

};

