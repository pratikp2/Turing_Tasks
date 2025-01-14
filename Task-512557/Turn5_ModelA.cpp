#include <iostream>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <map>
#include <condition_variable>
#include <iomanip> // For std::put_time
#include <sstream> // For std::ostringstream

class Config {
private:
    std::map<std::string, std::string> settings;
    mutable std::shared_mutex mtx;
    std::condition_variable_any cv; // To manage waiting readers and writers
    int activeReaders = 0; // Count of active readers
    int waitingWriters = 0; // Count of waiting writers

    void logWaitingTime(const std::string& threadName, const std::chrono::duration<double, std::milli>& waitTime) {
        std::ostringstream logStream;
        logStream << std::fixed << std::setprecision(2);
        logStream << "[" << threadName << "] waited for " << waitTime.count() << " ms.";
        std::cout << logStream.str() << std::endl; // Log to console
    }

public:
    Config() = default;

    // Reader function to retrieve a configuration value.
    // Adds a timeout parameter for waiting.
    bool get(const std::string& key, const std::string& threadName, std::chrono::milliseconds timeout) {
        auto startTime = std::chrono::steady_clock::now(); // Start timing
        std::unique_lock<std::shared_mutex> lock(mtx); // Lock for modifying shared state
        
        // Wait until there are no waiting writers, with timeout
        bool notified = cv.wait_for(lock, timeout, [this]() { return waitingWriters == 0; });

        // If the waiting time gets exceeded, return false
        if (!notified) {
            return false; 
        }

        // Now we can safely read the settings
        ++activeReaders; // Increase count of active readers
        lock.unlock(); // Unlock shared mutex to allow writers to proceed

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
        --activeReaders;
        if (activeReaders == 0) {
            cv.notify_all(); // Notify waiting writers if no active readers
        }

        // Log waiting time
        auto endTime = std::chrono::steady_clock::now(); // End timing
        logWaitingTime(threadName, endTime - startTime); 

        return true; // Indicate successful read
    }

    // Writer function to update a configuration value.
    // Adds a timeout parameter for waiting.
    bool update(const std::string& key, const std::string& value, const std::string& threadName, std::chrono::milliseconds timeout) {
        auto startTime = std::chrono::steady_clock::now(); // Start timing
        std::unique_lock<std::shared_mutex> lock(mtx);
        ++waitingWriters; // Increase count of waiting writers

        // Wait until there are no active readers, with timeout
        bool notified = cv.wait_for(lock, timeout, [this]() { return activeReaders == 0; });

        // If the waiting time gets exceeded, return false
        if (!notified) {
            --waitingWriters; // Decrease count of waiting writers, as we do not proceed
            return false; 
        }

        // Now we can safely write
        settings[key] = value;

        --waitingWriters;
        cv.notify_all(); // Notify all waiting threads

        // Log waiting time
        auto endTime = std::chrono::steady_clock::now(); // End timing
        logWaitingTime(threadName, endTime - startTime); 

        return true; // Indicate successful write
    }

    // Optional: A function to print all settings (for demonstration)
    void printSettings() {
        std::shared_lock lock(mtx); // Shared lock for read-only access
        for (const auto& pair : settings) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};