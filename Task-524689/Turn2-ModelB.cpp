#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <fstream>
#include <mutex>

// Custom strcpy implementation
char* my_strcpy(char* destination, const char* source) {
    char* original = destination;
    while ((*destination++ = *source++));
    return original;
}

// Custom strlen implementation
size_t my_strlen(const char* str) {
    const char* start = str;
    while (*str) {
        str++;
    }
    return str - start;
}

// Function to check for suspicious patterns in logs
bool contains_suspicious_pattern(const char* logEntry, const std::vector<const char*>& suspiciousPatterns) {
    for (const char* pattern : suspiciousPatterns) {
        if (strstr(logEntry, pattern) != nullptr) {
            return true; // Found a suspicious pattern
        }
    }
    return false; // No suspicious patterns found
}

// Function to process a log entry in parallel
void processLogEntry(const std::string& logEntry, const std::vector<const char*>& suspiciousPatterns, std::vector<std::string>& suspiciousEntries, std::mutex& mtx) {
    if (contains_suspicious_pattern(logEntry.c_str(), suspiciousPatterns)) {
        std::lock_guard<std::mutex> lock(mtx);
        suspiciousEntries.push_back(logEntry);
    }
}

int main() {
    const size_t MAX_LOG_LENGTH = 1024;

    // Vector of suspicious patterns to search for
    std::vector<const char*> suspiciousPatterns = {
        "error",
        "failed",
        "unauthorized",
        "access denied",
        "malicious"
    };

    // Vector to store suspicious log entries
    std::vector<std::string> suspiciousEntries;

    // Number of threads to use for parallel processing
    const int numThreads = 4; // You can adjust this based on your cloud environment resources
    std::thread threads[numThreads];
    std::mutex mtx;

    std::cout << "Reading log entries from file...\n";
    std::ifstream logFile("logs.txt"); // Replace this with the actual remote file path or storage system access
    
    std::string logEntry;
    if (logFile.is_open()) {
        while (std::getline(logFile, logEntry)) {
            // Create a copy of the log entry to pass to threads as strings cannot be shared
            std::string entryCopy = logEntry;

            int threadIndex = suspiciousEntries.size() % numThreads;
            threads[threadIndex] = std::thread(processLogEntry, entryCopy, suspiciousPatterns, std::ref(suspiciousEntries), std::ref(mtx));
        }

        for (int i = 0; i < numThreads; ++i) {
            threads[i].join();
        }

        logFile.close();

        std::cout << "\nAnalysis Complete:\n";
        std::cout << "Suspicious log entries found:\n";
        for (const std::string& entry : suspiciousEntries) {
            std::cout << entry << "\n";
        }
    } else {
        std::cout << "Failed to open the log file." << std::endl;
    }

    return 0;
}
