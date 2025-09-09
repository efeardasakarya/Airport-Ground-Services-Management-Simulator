#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <iostream>

class GlobalLogger {
public:
    static GlobalLogger* getInstance();


        // Basit, thread-safe loglar
        void printInfo(const std::string& msg);


        void printError(const std::string& msg);

        // Önemli log: kilitliyse kuyruğa al; değilse anında flush et
        void important(const std::string& msg);


        // Input kilidi: kilit altında INFO susturulur, IMPORTANT kuyruğa alınır
        void lockInput();

        void unlockInput();
   

private:
    GlobalLogger() = default;
    ~GlobalLogger() = default;

    std::mutex outMtx;
    std::atomic<bool> inputLocked{ false };

    std::mutex delayedMtx;
    std::queue<std::string> delayedImportant;
};
