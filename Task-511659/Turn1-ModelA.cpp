#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Simulates user choice based on their previous behavior
std::string makeDecision(const std::vector<std::string>& choices, const std::string& userProfile) {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness

    int decisionPath = rand() % choices.size(); // Randomly chooses an action
    printf("User Profile: %s\n", userProfile.c_str());
    printf("Decision Path Chosen: %s\n", choices[decisionPath].c_str());

    return choices[decisionPath];
}

// Simulates multiple user interactions
void analyzeUserBehavior() {
    std::vector<std::string> actions = {"Like", "Comment", "Share", "Follow"};
    std::string userProfile = "User123"; // Example user profile

    for (int i = 0; i < 5; ++i) { // Simulate 5 user decisions
        std::string decision = makeDecision(actions, userProfile);
        printf("User decided to: %s\n", decision.c_str());
    }
}

int main() {
    analyzeUserBehavior();
    return 0;
}
