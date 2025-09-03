#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <iostream>

class GlobalLogger {
public:
    static GlobalLogger* getInstance() {
        static GlobalLogger inst;
        return &inst;
    }

    // Basit, thread-safe loglar
    void printInfo(const std::string& msg) {
        if (inputLocked.load(std::memory_order_acquire)) return; // kilitliyken info sustur
        std::lock_guard<std::mutex> lk(outMtx);
        std::cout << "[INFO] " << msg << std::endl;
    }
    void printError(const std::string& msg) {
        // Hata her zaman yazılsın
        std::lock_guard<std::mutex> lk(outMtx);
        std::cerr << "[ERROR] " << msg << std::endl;
    }
    // Önemli log: kilitliyse kuyruğa al; değilse anında flush et
    void important(const std::string& msg) {
        if (inputLocked.load(std::memory_order_acquire)) {
            std::lock_guard<std::mutex> qlk(delayedMtx);
            delayedImportant.push(msg);
            return;
        }
        std::lock_guard<std::mutex> lk(outMtx);
        std::cout << "[IMPORTANT] " << msg << std::endl << std::flush;
    }

    // Input kilidi: kilit altında INFO susturulur, IMPORTANT kuyruğa alınır
    void lockInput() {
        inputLocked.store(true, std::memory_order_release);
    }
    void unlockInput() {
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

private:
    GlobalLogger() = default;
    ~GlobalLogger() = default;

    std::mutex outMtx;
    std::atomic<bool> inputLocked{ false };

    std::mutex delayedMtx;
    std::queue<std::string> delayedImportant;
};
