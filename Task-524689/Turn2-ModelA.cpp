#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

std::mutex logMutex; // Mutex for thread-safe logging

// Function to check for suspicious patterns in logs
bool contains_suspicious_pattern(const std::string& logEntry, const std::vector<std::string>& suspiciousPatterns) {
    for (const auto& pattern : suspiciousPatterns) {
        if (logEntry.find(pattern) != std::string::npos) {
            return true; // Found a suspicious pattern
        }
    }
    return false; // No suspicious patterns found
}

// Thread function for processing logs
void process_logs(const std::vector<std::string>& logs, const std::vector<std::string>& suspiciousPatterns) {
    for (const auto& log : logs) {
        if (contains_suspicious_pattern(log, suspiciousPatterns)) {
            std::lock_guard<std::mutex> guard(logMutex);
            std::cout << "Suspicious pattern detected in log: " << log << std::endl;
        }
    }
}

int main() {
    // Vector of suspicious patterns to search for
    std::vector<std::string> suspiciousPatterns = {
        "error",
        "failed",
        "unauthorized",
        "access denied",
        "malicious"
    };

    // Simulate reading logs from a cloud source
    std::vector<std::string> logEntries; // This would normally be filled via cloud API calls

    // Populate logEntries with simulated data for demonstration
    for (int i = 0; i < 100; i++) {
        logEntries.emplace_back("Log entry " + std::to_string(i) + ": This entry contains unauthorized access.");
        logEntries.emplace_back("Log entry " + std::to_string(i) + ": Normal operation message.");
        logEntries.emplace_back("Log entry " + std::to_string(i) + ": Error encountered in the system.");
    }

    // Determine number of threads to use
    const int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Launch threads to process log entries in parallel
    size_t logsPerThread = logEntries.size() / numThreads;
    for (int i = 0; i < numThreads; i++) {
        size_t startIdx = i * logsPerThread;
        size_t endIdx = (i == numThreads - 1) ? logEntries.size() : (i + 1) * logsPerThread;

        threads.emplace_back(process_logs, std::vector<std::string>(logEntries.begin() + startIdx, logEntries.begin() + endIdx), suspiciousPatterns);
    }

    // Join threads
    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
