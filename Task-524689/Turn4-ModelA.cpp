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
    if (str == nullptr) { // Handle null pointer
        std::cerr << "Input string is null!" << std::endl;
        return nullptr; // Return nullptr if input is null
    }
    
    // Handle empty string case
    if (*str == '\0') {
        std::cerr << "Input string is empty!" << std::endl;
        return nullptr; // Return nullptr for empty strings as well
    }

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
        "", // Adding an empty string for testing
        nullptr // Adding a null pointer for testing
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

    // Display copied strings and their lengths
    std::cout << "Copied Log Entries and their Lengths:" << std::endl;
    for (const char* str : copiedStrings) {
        std::cout << "Log Entry: \"" << str << "\""
                  << " | Length: " << strlen(str) << " characters" << std::endl; // Measure and print length
    }

    // Clean up dynamically allocated memory
    for (char* str : copiedStrings) {
        delete[] str; // Free each allocated string
    }

    return 0; // Successful termination
}
