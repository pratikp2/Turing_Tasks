#include <iostream>
#include <cstring>
#include <vector>

#define MAX_STRING_LENGTH 256 // Define a maximum length for each string

// Custom strcpy implementation
char* my_strcpy(char* destination, const char* source) {
    char* original = destination; // Save original pointer for return
    while ((*destination++ = *source++)); // Copy the string
    return original; // Return the original destination
}

// Function to allocate memory for a string and copy the content
char* allocate_and_copy(const char* str) {
    // Check for edge case: if str is null, return null
    if (str == nullptr) {
        std::cerr << "Error: Allocating memory for null pointer!" << std::endl;
        return nullptr;
    }

    char* newStr = new (std::nothrow) char[strlen(str) + 1]; // +1 for the null terminator

    if (newStr == nullptr) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return nullptr;
    }

    my_strcpy(newStr, str); // Copy the string into the allocated memory
    return newStr; // Return the pointer to the new string
}

// Function to calculate and print the string length, handling empty strings
void measure_string_length(const char* str) {
    if (str == nullptr) {
        std::cout << "String: (null)" << ", Length: " << "null" << std::endl;
    } else if (strlen(str) == 0) {
        std::cout << "String: " << str << ", Length: " << "0" << std::endl;
    } else {
        std::cout << "String: " << str << ", Length: " << strlen(str) << std::endl;
    }
}

int main() {
    // Simulated log entries (data extracted from forensic logs)
    std::vector<const char*> logEntries = {
        "User logged in from IP 192.168.1.1",
        "Access denied for user 'admin'",
        "Unauthorized access attempt detected!",
        "Error: database connection failed",
        "User 'guest' logged out successfully",
        nullptr // Added a null pointer to test edge case
    };

    std::vector<char*> copiedStrings;

    // Iterate over each log entry, copy it into dynamically allocated memory, and measure length
    for (const char* logEntry : logEntries) {
        char* copiedLogEntry = allocate_and_copy(logEntry);
        if (copiedLogEntry != nullptr) {
            copiedStrings.push_back(copiedLogEntry);
            measure_string_length(copiedLogEntry);
        }
    }

    // Clean up dynamically allocated memory
    for (char* str : copiedStrings) {
        delete[] str;
    }

    return 0; // Successful termination
}
