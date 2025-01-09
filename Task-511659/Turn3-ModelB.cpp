#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>

struct EngagementMetrics {
    int likes;
    int shares;
    int comments;

    EngagementMetrics() : likes(0), shares(0), comments(0) {}
};

// Function to dynamically allocate memory for a log message
char* allocateLogMessage(const std::string& message) {
    size_t length = message.length() + 1; // +1 for null terminator
    char* log = new char[length];
    strcpy(log, message.c_str());
    return log;
}

// Function to deallocate memory for a log message
void deallocateLogMessage(char* log) {
    delete[] log;
}

std::string makeDecision(const std::vector<std::string>& actions, EngagementMetrics& metrics) {
    int decisionPath = rand() % actions.size();
    std::string chosenAction = actions[decisionPath];

    if (chosenAction == "Like") {
        metrics.likes++;
    } else if (chosenAction == "Share") {
        metrics.shares++;
    } else if (chosenAction == "Comment") {
        metrics.comments++;
    }

    // Create a dynamically allocated log message
    std::string logMessage = fmt::format("User Action: {} | Likes: {}, Shares: {}, Comments: {}", 
                                          chosenAction, 
                                          metrics.likes, 
                                          metrics.shares, 
                                          metrics.comments);

    char* log = allocateLogMessage(logMessage);

    printf("%s\n", log);

    // Store the log in a vector
    logs.push_back(log);

    return chosenAction;
}

void analyzeUserBehavior() {
    std::vector<std::string> actions = {"Like", "Comment", "Share", "Follow"};
    EngagementMetrics metrics;

    for (int i = 0; i < 10; ++i) {
        makeDecision(actions, metrics);
    }

    // Perform any analysis on the logs here
    // For demonstration, we'll just print the total number of logs
    printf("Total number of logs: %zu\n", logs.size());

    // Deallocate memory for each log
    for (char* log : logs) {
        deallocateLogMessage(log);
    }

    // Clear the log vector
    logs.clear();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    analyzeUserBehavior();
    return 0;
}
