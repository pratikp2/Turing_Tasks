#include <iostream>
#include <cstring>
#include <vector>

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

int main() {
    const size_t MAX_LOG_LENGTH = 1024;
    char logEntry[MAX_LOG_LENGTH];

    // Vector of suspicious patterns to search for
    std::vector<const char*> suspiciousPatterns = {
        "error",
        "failed",
        "unauthorized",
        "access denied",
        "malicious"
    };

    std::cout << "Enter log entry (max " << MAX_LOG_LENGTH - 1 << " characters): ";
    std::cin.getline(logEntry, MAX_LOG_LENGTH);

    // Check the length of the log entry
    size_t length = my_strlen(logEntry);
    std::cout << "Log Entry Length: " << length << " characters" << std::endl;

    // Check for suspicious patterns
    if (contains_suspicious_pattern(logEntry, suspiciousPatterns)) {
        std::cout << "Suspicious pattern detected!" << std::endl;
    } else {
        std::cout << "No suspicious patterns found." << std::endl;
    }

    return 0;
}
