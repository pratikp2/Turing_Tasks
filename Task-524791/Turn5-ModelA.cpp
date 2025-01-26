#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <fstream>

enum class AIState {
    Idle,
    Patrol,
    Chase
};

// Define platform types
enum class Platform {
    PC,
    PlayStation5
};

class AI {
public:
    AI(Platform platform) : currentState(AIState::Idle), currentPlatform(platform) {
        stateEntryTimes[AIState::Idle] = std::chrono::high_resolution_clock::now();
    }

    void Update() {
        auto now = std::chrono::high_resolution_clock::now();

        switch (currentState) {
            case AIState::Idle:
                TrackStateTime(now);
                HandleIdle();
                break;

            case AIState::Patrol:
                TrackStateTime(now);
                HandlePatrol();
                break;

            case AIState::Chase:
                TrackStateTime(now);
                HandleChase();
                break;

            default:
                break;
        }
    }

    void Input(const std::string& input) {
        if (input == "see_player") {
            SetState(AIState::Chase);
        } else if (input == "lost_player") {
            SetState(AIState::Patrol);
        } else if (input == "patrol_complete") {
            SetState(AIState::Idle);
        }
    }

    void LogProfileData() {
        std::ofstream outFile("AI_Profile_Data.csv", std::ios::app);
        if (outFile.is_open()) {
            outFile << "Platform,State,Duration (seconds)\n";
            for (const auto& duration_entry : stateDurations) {
                std::string stateName;
                switch (duration_entry.first) {
                    case AIState::Idle: stateName = "Idle"; break;
                    case AIState::Patrol: stateName = "Patrol"; break;
                    case AIState::Chase: stateName = "Chase"; break;
                }
                outFile << (currentPlatform == Platform::PC ? "PC" : "PlayStation 5") << ","
                         << stateName << ","
                         << duration_entry.second.count() << "\n";
            }
            outFile.close();
        } else {
            std::cerr << "Unable to open file for logging profile data.\n";
        }
    }

private:
    AIState currentState;
    Platform currentPlatform;
    std::unordered_map<AIState, std::chrono::high_resolution_clock::time_point> stateEntryTimes;
    std::unordered_map<AIState, std::chrono::duration<double>> stateDurations;

    void HandleIdle() {
        std::cout << "AI is currently idle.\n";
        if (ShouldStartPatrolling()) {
            std::cout << "AI decides to patrol.\n";
            SetState(AIState::Patrol);
        }
    }

    void HandlePatrol() {
        std::cout << "AI is patrolling.\n";
        if (DetectPlayer()) {
            std::cout << "AI sees the player!\n";
            SetState(AIState::Chase);
        }
    }

    void HandleChase() {
        std::cout << "AI is chasing the player!\n";
        if (PlayerOutOfSight()) {
            std::cout << "AI lost sight of the player and will patrol now.\n";
            SetState(AIState::Patrol);
        }
    }

    void TrackStateTime(const std::chrono::high_resolution_clock::time_point& now) {
        auto previousState = currentState;
        if (stateEntryTimes.find(previousState) != stateEntryTimes.end()) {
            auto duration = now - stateEntryTimes[previousState];
            stateDurations[previousState] += duration;
        }
        stateEntryTimes[currentState] = now;
    }

    bool DetectPlayer() {
        return false; // Replace with real detection logic
    }

    bool ShouldStartPatrolling() {
        return true; // Placeholder logic
    }

    bool PlayerOutOfSight() {
        return true; // Placeholder logic
    }

    void SetState(AIState newState) {
        currentState = newState;
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now - stateEntryTimes[static_cast<AIState>(currentState)];
        stateDurations[currentState] += duration;
        stateEntryTimes[currentState] = now;
    }
};

// Example usage
int main() {
    // Choose platform: PC or PlayStation 5
    Platform platform = Platform::PC; // Change to Platform::PlayStation5 as needed
    AI ai(platform);

    // Simulate game loop with input commands
    std::string commands[] = { "see_player", "lost_player", "patrol_complete", "see_player" };
    for (const auto& command : commands) {
        std::cout << "Input: " << command << "\n";
        ai.Input(command);
        ai.Update();
    }

    // Log the time spent in each state to a file
    ai.LogProfileData();

    return 0;
}
