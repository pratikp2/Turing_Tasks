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

    // Utility function to log the waiting time
    void logWaitingTime(const std::string& threadName, const std::chrono::duration<double, std::milli>& waitTime) {
        std::ostringstream logStream;
        logStream << std::fixed << std::setprecision(2);
        logStream << "[" << threadName << "] waited for " << waitTime.count() << " ms.";
        std::cout << logStream.str() << std::endl; // Log to console, but can be adapted to file or other logging systems
    }

public:
    Config() = default;

    // Reader function to retrieve a configuration value.
    std::string get(const std::string& key, const std::string& threadName) {
        auto startTime = std::chrono::steady_clock::now(); // Start timing
        std::unique_lock<std::shared_mutex> lock(mtx); // Lock for modifying shared state
        // Wait until there are no waiting writers
        cv.wait(lock, [this]() { return waitingWriters == 0; });

        // Now we can safely read the settings
        ++activeReaders; // Increase count of active readers
        lock.unlock(); // Unlock the shared mutex to allow writers

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

        // Log waiting time
        auto endTime = std::chrono::steady_clock::now(); // End timing
        logWaitingTime(threadName, endTime - startTime); // Log the time spent waiting

        return value; // Return the read value
    }

    // Writer function to update a configuration value.
    void update(const std::string& key, const std::string& value, const std::string& threadName) {
        auto startTime = std::chrono::steady_clock::now(); // Start timing
        std::unique_lock<std::shared_mutex> lock(mtx);
        ++waitingWriters; // Increase count of waiting writers

        // Wait until there are no active readers
        cv.wait(lock, [this]() { return activeReaders == 0; });

        // Now we can safely write
        settings[key] = value;

        --waitingWriters; // Decrease count of waiting writers
        cv.notify_all(); // Notify all waiting threads (readers and writers)

        // Log waiting time
        auto endTime = std::chrono::steady_clock::now(); // End timing
        logWaitingTime(threadName, endTime - startTime); // Log the time spent waiting
    }

    // Optional: A function to print all settings (for demonstration)
    void printSettings() {
        std::shared_lock lock(mtx); // Shared lock for read-only access
        for (const auto& pair : settings) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};