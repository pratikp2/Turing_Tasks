#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <sstream>

enum class AIState {
    Idle,
    Patrol,
    Chase
};

class AI {
public:
    AI() : currentState(AIState::Idle), platform("Unknown") {
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

    void SetPlatform(const std::string& platformName) {
        platform = platformName;
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

    void SaveProfilesToFile(const std::string& fileName) {
        std::ofstream outputFile(fileName);
        outputFile << "Platform: " << platform << "\n";
        outputFile << "--- AI State Profiling Data ---\n";

        for (const auto& duration_entry : stateDurations) {
            std::string stateName;
            switch (duration_entry.first) {
                case AIState::Idle: stateName = "Idle"; break;
                case AIState::Patrol: stateName = "Patrol"; break;
                case AIState::Chase: stateName = "Chase"; break;
            }
            outputFile << stateName << ": " << duration_entry.second.count() << " seconds\n";
        }
        outputFile.close();
    }

private:
    AIState currentState;
    std::string platform;
    std::unordered_map<AIState, std::chrono::high_resolution_clock::time_point> stateEntryTimes;
    std::unordered_map<AIState, std::chrono::duration<double>> stateDurations;

    // Same implementation for handle state methods and trackStateTime function (kept for brevity)
};

// Example usage to collect profiling data
int main() {
    AI ai;
    ai.SetPlatform("PlayStation 5"); // Replace with the appropriate platform name

    std::string commands[] = { "see_player", "lost_player", "patrol_complete", "see_player" };
    for (const auto& command : commands) {
        ai.Input(command);
        ai.Update();
    }

    // Log and save profiling data to a file
    ai.SaveProfilesToFile("ai_profiling_ps5.txt");

    return 0;
}
