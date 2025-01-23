#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>

using namespace std;

// Function to copy strings into dynamically allocated memory
vector<char*> copyStringsToDynamicMemory(const vector<string>& logStrings) {
    vector<char*> dynamicallyAllocatedStrings;

    // Loop through each log string
    for (const string& logString : logStrings) {
        size_t stringLength = logString.length() + 1; // +1 for the null terminator

        // Dynamically allocate memory for the copied string
        char* copiedString = new char[stringLength];
        if (copiedString == nullptr) {
            throw runtime_error("Memory allocation failed");
        }

        // Copy the string into the dynamically allocated memory
        strcpy(copiedString, logString.c_str());
        dynamicallyAllocatedStrings.push_back(copiedString);
    }

    return dynamicallyAllocatedStrings;
}

int main() {
    // Simulate a list of strings extracted from forensic logs
    vector<string> logStrings = {
        "This is a log entry from a forensic data source.",
        "Another log entry with sensitive information.",
        "System error occurred at 14:25:32.",
        "User access attempt detected.",
        "Malicious activity identified in the network."
    };

    try {
        // Copy the strings into dynamically allocated memory
        vector<char*> dynamicallyAllocatedLogs = copyStringsToDynamicMemory(logStrings);

        // Display the dynamically allocated strings
        cout << "\nDynamically Allocated Log Entries:\n";
        for (char* log : dynamicallyAllocatedLogs) {
            cout << log << endl;
        }

        // It's important to free the dynamically allocated memory
        for (char* log : dynamicallyAllocatedLogs) {
            delete[] log;
        }
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
