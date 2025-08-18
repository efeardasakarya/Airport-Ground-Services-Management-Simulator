#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"
#include <string>

class Logger
{

public:
	void createLog(const std::string& logger);

	void createErrorLog(const std::string& errorLogger);

	void printInfo(const std::string& InfoMessage , const std::string& loggerName);

	void printError(const std::string& ErrorMessage, const std::string& loggerName);

	// in the future process print and create functions going to be merged.

	void createMultiSink();

	void asyncMultiSink();

};

