#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Categorize user action
std::string categorizeUserAction(const std::string& action) {
    if (action == "Like") {
        return "Like";
    } else if (action == "Share") {
        return "Share";
    } else if (action == "Comment") {
        return "Comment";
    } else {
        return "Other";
    }
}

// Simulate user choice based on their previous behavior
std::string makeDecision(const std::vector<std::string>& choices, const std::string& userProfile) {
    srand(static_cast<unsigned int>(time(0)));

    int decisionPath = rand() % choices.size();
    std::string action = choices[decisionPath];

    printf("User Profile: %s\n", userProfile.c_str());
    printf("Decision Path Chosen: %s\n", action.c_str());

    std::string category = categorizeUserAction(action);
    printf("User Behavior Category: %s\n", category.c_str());

    return action;
}

void analyzeUserBehavior() {
    std::vector<std::string> actions = {"Like", "Comment", "Share", "Follow", "View", "Save"};
    std::string userProfile = "User456";

    for (int i = 0; i < 10; ++i) {
        std::string decision = makeDecision(actions, userProfile);
        printf("User decided to: %s\n", decision.c_str());
    }
}

int main() {
    analyzeUserBehavior();
    return 0;
}
