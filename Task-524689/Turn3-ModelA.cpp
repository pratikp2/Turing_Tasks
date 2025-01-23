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
    // Allocate memory for the string
    char* newStr = new (std::nothrow) char[strlen(str) + 1]; // +1 for the null terminator
    if (newStr == nullptr) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return nullptr; // Return nullptr if allocation fails
    }
    my_strcpy(newStr, str); // Copy the string into the allocated memory
    return newStr; // Return the pointer to the new string
}

int main() {
    // Simulated log entries (data extracted from forensic logs)
    std::vector<const char*> logEntries = {
        "User logged in from IP 192.168.1.1",
        "Access denied for user 'admin'",
        "Unauthorized access attempt detected!",
        "Error: database connection failed",
        "User 'guest' logged out successfully",
    };

    // Dynamic array to hold copied strings
    std::vector<char*> copiedStrings;

    // Iterate over each log entry and copy it into dynamically allocated memory
    for (const char* logEntry : logEntries) {
        char* copiedLogEntry = allocate_and_copy(logEntry); // Allocate and copy the string
        if (copiedLogEntry != nullptr) { // Check for successful allocation
            copiedStrings.push_back(copiedLogEntry); // Store the pointer
        }
    }

    // Display copied strings
    std::cout << "Copied Log Entries:" << std::endl;
    for (const char* str : copiedStrings) {
        std::cout << str << std::endl; // Print each copied string
    }

    // Clean up dynamically allocated memory
    for (char* str : copiedStrings) {
        delete[] str; // Free each allocated string
    }

    return 0; // Successful termination
}
