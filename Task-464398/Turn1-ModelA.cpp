#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::mutex logMutex;

enum class ErrorCode {
    NONE = 0,
    FILE_NOT_FOUND,
    ACCESS_DENIED,
    NETWORK_ERROR,
    OUT_OF_MEMORY,
    UNKNOWN_ERROR
};

void logError(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::cout << "Error: " << message << std::endl;
}

void handleError(ErrorCode code) {
    switch (code) {
        case ErrorCode::NONE:
            break;
        case ErrorCode::FILE_NOT_FOUND:
            logError("File not found.");
            break;
        case ErrorCode::ACCESS_DENIED:
            logError("Access denied.");
            break;
        case ErrorCode::NETWORK_ERROR:
            logError("Network error occurred.");
            break;
        case ErrorCode::OUT_OF_MEMORY:
            logError("Out of memory.");
            break;
        case ErrorCode::UNKNOWN_ERROR:
            logError("An unknown error occurred.");
            break;
        default:
            logError("Unhandled error code.");
            break;
    }
}

void worker(int id) {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
    
    // Simulate an error for demonstration
    ErrorCode error = static_cast<ErrorCode>(id % 5);
    handleError(error);
}

int main() {
    const int numThreads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
