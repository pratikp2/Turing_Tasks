#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Structure to hold engagement metrics
struct EngagementMetrics {
    int likes;
    int shares;
    int comments;

    EngagementMetrics() : likes(0), shares(0), comments(0) {}
};

// Simulates user choices and logs the engagement metrics
std::string makeDecision(const std::vector<std::string>& actions, EngagementMetrics& metrics) {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness

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

    // Log the choices and metrics
    printf("User Action: %s | Likes: %d, Shares: %d, Comments: %d\n", 
           chosenAction.c_str(), 
           metrics.likes, 
           metrics.shares, 
           metrics.comments);
    
    return chosenAction;
}

// Simulates multiple user interactions
void analyzeUserBehavior() {
    std::vector<std::string> actions = {"Like", "Comment", "Share", "Follow"};
    EngagementMetrics metrics; // Initialize engagement metrics

    for (int i = 0; i < 10; ++i) { // Simulate 10 user decisions
        makeDecision(actions, metrics);
    }
}

int main() {
    analyzeUserBehavior();
    return 0;
}
