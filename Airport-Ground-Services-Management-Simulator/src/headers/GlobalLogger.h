#pragma once

#include <string>
#include <atomic>
#include <mutex>
#include <deque>
#include <memory>
#include <queue>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/async.h"

class GlobalLogger
{
private:
    static GlobalLogger* instance;

    
    std::shared_ptr<spdlog::logger> asyncLogger;
    std::shared_ptr<spdlog::logger> immediateLogger;

   
    GlobalLogger();
    ~GlobalLogger();

    bool inputLocked = false;
    std::queue<std::string> delayedImportant;

public:
    GlobalLogger(const GlobalLogger&) = delete;
    GlobalLogger& operator=(const GlobalLogger&) = delete;

    static GlobalLogger* getInstance();

    void asyncMultiSink();
   
    // === Normal loglar (input sırasında düşer) ===
    void printInfo(const std::string& infoMessage);
    void printError(const std::string& infoMessage);

    void important(const std::string& importantMessage);
    void userInputMessage(const std::string& inputMessage);


    void lockInput();
    void unlockInput();

   
   
};
