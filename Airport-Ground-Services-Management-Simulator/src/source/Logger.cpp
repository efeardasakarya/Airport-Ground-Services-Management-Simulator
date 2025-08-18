#include "Logger.h"

void Logger::createLog(const std::string& logger)
{
	auto temp = spdlog::stdout_color_mt(logger);
}

void Logger::createErrorLog(const std::string& errorLogger)
{
	auto temp = spdlog::stderr_color_mt("errorLogger");
}

void Logger::printInfo(const std::string& InfoMessage, const std::string& loggerName)
{
	spdlog::get(loggerName)->info(InfoMessage);
}

void Logger::printError(const std::string& ErrorMessage, const std::string& loggerName)
{
	spdlog::get(loggerName)->error(ErrorMessage);
}

void Logger::createMultiSink()
{
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_level(spdlog::level::warn); // just print logs higher than warn. "trace < debug < info < warn < err < critical < off"

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", false);
	fileSink->set_level(spdlog::level::trace); //Get all log level to file


	spdlog::logger logger("multi sink	", { consoleSink ,fileSink } );
	logger.set_level(spdlog::level::debug);

	logger.warn("this should appear in both console and file");
	logger.info("this message should not appear in the console, only in the file");
}

void Logger::asyncMultiSink()
{
	spdlog::init_thread_pool(8192, 1); // A queue for the log messages will write after main program
	auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
	auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("mylog.txt", 1024 * 1024 * 10, 3);
	// Create 3 file 10MB. When all files are full automatically delete the oldest file and continue writing.

	std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink };
	auto asyncLogger = std::make_shared<spdlog::async_logger>("asyncLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	spdlog::register_logger(asyncLogger);
}
