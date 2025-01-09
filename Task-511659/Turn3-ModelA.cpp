#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Structure to hold engagement metrics
struct EngagementMetrics {
    int likes;
    int shares;
    int comments;

    EngagementMetrics() : likes(0), shares(0), comments(0) {}
};

// Log entry structure
struct LogEntry {
    char* message; // Dynamically allocated message
    LogEntry* next; // Pointer to the next log entry

    LogEntry(const char* msg) {
        message = new char[strlen(msg) + 1]; // Allocate memory for the message
        strcpy(message, msg); // Copy the message
        next = nullptr;
    }

    ~LogEntry() {
        delete[] message; // Deallocate memory for the message
    }
};

// Log list structure
struct LogList {
    LogEntry* head;

    LogList() : head(nullptr) {}

    // Function to add a log entry
    void addLog(const char* msg) {
        LogEntry* newEntry = new LogEntry(msg);
        newEntry->next = head; // Insert at head for simplicity
        head = newEntry;
    }

    // Function to print all logs and deallocate memory
    void printAndClearLogs() {
        LogEntry* current = head;
        while (current) {
            std::cout << current->message << std::endl;
            LogEntry* temp = current;
            current = current->next;
            delete temp; // Deallocate each log entry
        }
        head = nullptr; // Reset head to indicate logs are cleared
    }

    ~LogList() {
        printAndClearLogs(); // Ensure all logs are cleared on destruction
    }
};

// Simulates user choices and logs the engagement metrics
std::string makeDecision(const std::vector<std::string>& actions, EngagementMetrics& metrics, LogList& logs) {
    int decisionPath = rand() % actions.size(); // Randomly pick an action
    std::string chosenAction = actions[decisionPath];

    // Increment respective metric based on usage
    if (chosenAction == "Like") {
        metrics.likes++;
    } else if (chosenAction == "Share") {
        metrics.shares++;
    } else if (chosenAction == "Comment") {
        metrics.comments++;
    }

    // Create log message
    char logMessage[256];
    snprintf(logMessage, sizeof(logMessage), "User Action: %s | Likes: %d, Shares: %d, Comments: %d", 
             chosenAction.c_str(), 
             metrics.likes, 
             metrics.shares, 
             metrics.comments);
    
    // Add log message to the log list
    logs.addLog(logMessage);
    
    return chosenAction;
}

// Simulates multiple user interactions
void analyzeUserBehavior() {
    std::vector<std::string> actions = {"Like", "Comment", "Share", "Follow"};
    EngagementMetrics metrics; // Initialize engagement metrics
    LogList logs; // Initialize log list

    for (int i = 0; i < 10; ++i) { // Simulate 10 user decisions
        makeDecision(actions, metrics, logs);
    }

    // After all actions, print and clear logs
    logs.printAndClearLogs();
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    analyzeUserBehavior();
    return 0;
}
