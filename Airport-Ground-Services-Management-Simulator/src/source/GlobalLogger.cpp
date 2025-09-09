#include "GlobalLogger.h"


GlobalLogger* GlobalLogger::getInstance()
{
    static GlobalLogger inst;
    return &inst;
}

// Basic logs
void GlobalLogger::printInfo(const std::string& msg)
{
    if (inputLocked.load(std::memory_order_acquire)) return; // kilitliyken info sustur
    std::lock_guard<std::mutex> lk(outMtx);
    std::cout << "[INFO] " << msg << std::endl;
}

// Errors
void GlobalLogger::printError(const std::string& msg)
{
    // Hata her zaman yazılsın
    std::lock_guard<std::mutex> lk(outMtx);
    std::cerr << "[ERROR] " << msg << std::endl;
}

// important logs, can't mute : add to queue if locked ; if not immediate flush
void GlobalLogger::important(const std::string& msg)
{
    if (inputLocked.load(std::memory_order_acquire))
    {
        std::lock_guard<std::mutex> qlk(delayedMtx);
        delayedImportant.push(msg);
        return;
    }
    std::lock_guard<std::mutex> lk(outMtx);
    std::cout << "[IMPORTANT] " << msg << std::endl << std::flush;
}

// Input lock : Lock while getting input from user. Mute and ignore infos , queue importants
void GlobalLogger::lockInput()
{
    inputLocked.store(true, std::memory_order_release);
}
void GlobalLogger::unlockInput()
{
    // Kuyruğu boşalt
    std::queue<std::string> tmp;
    {
        std::lock_guard<std::mutex> qlk(delayedMtx);
        std::swap(tmp, delayedImportant);
    }
    inputLocked.store(false, std::memory_order_release);

    std::lock_guard<std::mutex> lk(outMtx);
    while (!tmp.empty()) {
        std::cout << "[IMPORTANT] " << tmp.front() << std::endl << std::flush;
        tmp.pop();
    }
}