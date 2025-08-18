#include "GlobalLogger.h"
GlobalLogger* GlobalLogger::instance = nullptr;



GlobalLogger::GlobalLogger()
{

}



GlobalLogger::~GlobalLogger()
{

}



void GlobalLogger::printInfo(const std::string& InfoMessage, const std::string& loggerName)
{
	spdlog::get(loggerName)->info(InfoMessage);
}



void GlobalLogger::printError(const std::string& ErrorMessage, const std::string& loggerName)
{
	spdlog::get(loggerName)->error(ErrorMessage);
}



void GlobalLogger::asyncMultiSink(const std::string& LogMessage)
{
	spdlog::init_thread_pool(8192, 1); // A queue for the log messages will write after main program
	auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
	auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("mylog.txt", 1024 * 1024 * 10, 3);
	// Create 3 file 10MB. When all files are full automatically delete the oldest file and continue writing.

	std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink };
	auto asyncLogger = std::make_shared<spdlog::async_logger>("asyncLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	spdlog::register_logger(asyncLogger);



}



