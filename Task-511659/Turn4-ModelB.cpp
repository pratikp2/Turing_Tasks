#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <map>

#define TOTAL_SIMULATED_SECONDS 3600  // 1 hour in seconds for simulating log entries

struct EngagementMetrics {
    int likes;
    int shares;
    int comments;
    EngagementMetrics() : likes(0), shares(0), comments(0) {}
};

struct LogEntry {
    char* message; // Dynamically allocated message
    long timeStamp; // Timestamp of the log entry
    LogEntry* next; // Pointer to the next log entry

    LogEntry(const char* msg, long timestamp) {
        message = new char[strlen(msg) + 1];
        strcpy(message, msg);
        timeStamp = timestamp;
        next = nullptr;
    }

    ~LogEntry() {
        delete[] message;
    }
};

struct LogList {
    LogEntry* head;

    LogList() : head(nullptr) {}

    void addLog(const char* msg, long timestamp) {
        LogEntry* newEntry = new LogEntry(msg, timestamp);
        newEntry->next = head;
        head = newEntry;
    }

    void printAndClearLogs() {
        LogEntry* current = head;
        while (current) {
            printf("%ld: %s\n", current->timeStamp, current->message);
            LogEntry* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    ~LogList() {
        printAndClearLogs();
    }
};

void simulateLoggedInteractions(LogList& logs, EngagementMetrics& metrics) {
    const std::vector<std::string> actions = {"Like", "Comment", "Share", "Follow"};
    int currentSec = 0;

    while (currentSec <= TOTAL_SIMULATED_SECONDS) {
        int decisionPath = rand() % actions.size();
        std::string chosenAction = actions[decisionPath];

        metrics.likes += chosenAction == "Like" ? 1 : 0;
        metrics.shares += chosenAction == "Share" ? 1 : 0;
        metrics.comments += chosenAction == "Comment" ? 1 : 0;

        char logMessage[256];
        snprintf(logMessage, sizeof(logMessage), "User Action: %s | Likes: %d, Shares: %d, Comments: %d", 
                 chosenAction.c_str(), metrics.likes, metrics.shares, metrics.comments);

        logs.addLog(logMessage, currentSec);
        currentSec += rand() % 30 + 1; // Events in random intervals
    }
}

// Analyze logs to identify peak engagement times and patterns
void analyzeLogs(LogList& logs) {
    std::map<long, int> actionCountsPerSec; // Maps timestamp to action counts

    LogEntry* current = logs.head;
    while (current) {
        actionCountsPerSec[current->timeStamp]++;
        current = current->next;
    }

    int peakEngagementStart, peakEngagementEnd;
    int maxEngagement = 0;
    long peakTime = 0;

    for (const auto& entry : actionCountsPerSec) {
        if (entry.second > maxEngagement) {
            maxEngagement = entry.second;
            peakTime = entry.first;
        }
    }

    printf("\nPeak Engagement Analysis:\n");
    printf("  Peak Engagement Time: %ld seconds into the simulation\n", peakTime);
    printf("  Highest Engagement Level: %d actions\n", maxEngagement);

    // Add other analytical patterns detection as needed
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    LogList logs; // Initialize log list
    EngagementMetrics metrics; // Initialize engagement metrics

    simulateLoggedInteractions(logs, metrics);

    // After all actions, print and clear logs
    logs.printAndClearLogs();

    analyzeLogs(logs);

    return 0;
}
