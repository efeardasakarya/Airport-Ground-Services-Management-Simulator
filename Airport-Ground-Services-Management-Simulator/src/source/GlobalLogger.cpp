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
}


void GlobalLogger::asyncMultiSink()

{
	spdlog::init_thread_pool(8192, 1);

	auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();

	auto dailySink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/daidaily.txt", 0, 0, false, 30);

	std::vector<spdlog::sink_ptr> sinks{ stdoutSink, dailySink };

	// Async logger setup
	asyncLogger = std::make_shared<spdlog::async_logger>("asyncLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

	spdlog::register_logger(asyncLogger);

	// Sync (immediate logger setup
	immediateLogger = std::make_shared<spdlog::logger>("immediateLogger", sinks.begin(), sinks.end());
	immediateLogger->set_level(spdlog::level::info);
	// Important'ta biz manuel flush edeceğiz; yine de güvenlik için:
	immediateLogger->flush_on(spdlog::level::trace);



}


void GlobalLogger::printInfo(const std::string& InfoMessage)
{
	if (inputLocked)
	{
		return;
	}

	if (asyncLogger)
	{
		asyncLogger->info(InfoMessage);
	}
}

void GlobalLogger::printError(const std::string& ErrorMessage)
{
	if (inputLocked)
	{
		asyncLogger->error(ErrorMessage);
	}
}

void GlobalLogger::important(const std::string& importantMessage)
{
	if(inputLocked)
	{
		delayedImportant.push(importantMessage);
		return;
	}

	if (immediateLogger)
	{
		immediateLogger->info(importantMessage);
		immediateLogger->flush();
	}

}

void GlobalLogger::lockInput()
{
	inputLocked = true;
}

void GlobalLogger::unlockInput()
{
	std::queue <std::string> delayed;

	inputLocked = false;

	swap(delayed, delayedImportant);

	while (!delayed.empty())
	{
		if (immediateLogger)
		{
			immediateLogger->info(delayed.front());
			immediateLogger->flush();
		}
		delayed.pop();
	}



}
 // Specified function to print log while getting input like "Do you want to add any tasks (Y/N)?
void GlobalLogger::userInputMessage(const std::string& inputMessage)
{
	immediateLogger->info(inputMessage);
	immediateLogger->flush();
}
