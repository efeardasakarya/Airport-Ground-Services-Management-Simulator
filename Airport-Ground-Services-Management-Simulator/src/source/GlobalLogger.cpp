#include "GlobalLogger.h"
GlobalLogger* GlobalLogger::instance = nullptr;



GlobalLogger::GlobalLogger()
{
	
}



GlobalLogger::~GlobalLogger()
{

}

GlobalLogger* GlobalLogger::getInstance()
{
	if (instance == nullptr)
	{
		static GlobalLogger instance;
		
		return &instance;
		
		
	}
	return instance;
}



void GlobalLogger::printInfo(const std::string& InfoMessage )
{
	
	asyncLogger->info(InfoMessage);
}



void GlobalLogger::printError(const std::string& ErrorMessage)
{
	
	asyncLogger->error(ErrorMessage);
}



void GlobalLogger::asyncMultiSink()
{
	spdlog::init_thread_pool(8192, 1); // A queue for the log messages will write after main program
	auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
	auto dailySink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/daidaily.txt", 0, 0, false, 30);
	

	std::vector<spdlog::sink_ptr> sinks { stdoutSink, dailySink };
	asyncLogger = std::make_shared<spdlog::async_logger>("asyncLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	spdlog::register_logger(asyncLogger);

	

}



