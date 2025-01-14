#include <iostream>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <map>
#include <condition_variable>
#include <atomic>
#include <fstream>

class Config {
private:
    std::map<std::string, std::string> settings;
    mutable std::shared_mutex mtx;
    std::condition_variable_any cv; // To manage waiting readers and writers
    int activeReaders = 0; // Count of active readers
    int waitingWriters = 0; // Count of waiting writers
    std::atomic_uint_fast64_t nextThreadId = 1; // For unique thread identifiers in logs
    std::ofstream logFile;

public:
    Config(const std::string& logFilePath)
        : logFile(logFilePath)
    {
        if (!logFile.is_open()) {
            std::cerr << "Error: Cannot open log file " << logFilePath << std::endl;
        }
    }

    // Helper function to log the wait time
    void logWaitTime(std::chrono::duration<double> waitTime, const std::thread::id& threadId) const {
        logFile << "Thread " << threadId << " (ID " << nextThreadId.fetch_add(1) << ") waited for " << waitTime.count() << " seconds" << std::endl;
    }

    // Reader function to retrieve a configuration value.
    std::string get(const std::string& key) {
        std::unique_lock<std::shared_mutex> lock(mtx); // Lock for modifying shared state
        auto startTime = std::chrono::high_resolution_clock::now();

        // Wait until there are no waiting writers
        cv.wait(lock, [this]() { return waitingWriters == 0; });

        auto endTime = std::chrono::high_resolution_clock::now();
        auto waitTime = endTime - startTime;

        // Now we can safely read the settings
        ++activeReaders; // Increase count of active readers
        lock.unlock(); // Unlock the shared mutex to allow writers

        // Perform the read operation
        std::string value;
        {
            std::shared_lock readLock(mtx); // Acquire shared lock for reading
            auto it = settings.find(key);
            if (it != settings.end()) {
                value = it->second;
            }
        }

        // Done reading, decrease reader count
        lock.lock();
        --activeReaders; // Decrease count of active readers
        if (activeReaders == 0) {
            cv.notify_all(); // Notify waiting writers if no active readers
        }

        logWaitTime(waitTime, std::this_thread::get_id());
        return value; // Return the read value
    }

    // Writer function to update a configuration value.
    void update(const std::string& key, const std::string& value) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        auto startTime = std::chrono::high_resolution_clock::now();

        ++waitingWriters; // Increase count of waiting writers

        // Wait until there are no active readers
        cv.wait(lock, [this]() { return activeReaders == 0; });

        auto endTime = std::chrono::high_resolution_clock::now();
        auto waitTime = endTime - startTime;

        // Now we can safely write
        settings[key] = value;

        --waitingWriters; // Decrease count of waiting writers
        cv.notify_all(); // Notify all waiting threads (readers and writers)

        logWaitTime(waitTime, std::this_thread::get_id());
    }

    // Optional: A function to print all settings (for demonstration)
    void printSettings() {
        std::shared_lock lock(mtx); // Shared lock for read-only access
        for (const auto& pair : settings) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};