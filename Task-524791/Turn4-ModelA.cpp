#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>

enum class AIState {
    Idle,
    Patrol,
    Chase
};

class AI {
public:
    AI() : currentState(AIState::Idle) {
        stateEntryTimes[AIState::Idle] = std::chrono::high_resolution_clock::now();
    }

    void Update() {
        auto now = std::chrono::high_resolution_clock::now();

        switch (currentState) {
            case AIState::Idle:
                TrackStateTime(now);  // Track time spent in the previous state before entering a new state
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
        // This function simulates external inputs that change the AI state
        if (input == "see_player") {
            SetState(AIState::Chase);
        } else if (input == "lost_player") {
            SetState(AIState::Patrol);
        } else if (input == "patrol_complete") {
            SetState(AIState::Idle);
        }
    }

private:
    AIState currentState;
    std::unordered_map<AIState, std::chrono::high_resolution_clock::time_point> stateEntryTimes;
    std::unordered_map<AIState, std::chrono::duration<double>> stateDurations;

    void HandleIdle() {
        std::cout << "AI is currently idle.\n";
        // Example condition to transition to patrol (for demonstration purposes)
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
        // Update entry time for the new state
        stateEntryTimes[currentState] = now;
    }

    // Placeholder functions for game logic
    bool DetectPlayer() {
        // Implement actual detection logic
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

        // Log the time spent in the previous state
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now - stateEntryTimes[static_cast<AIState>(currentState)];
        stateDurations[currentState] += duration;

        // Move current time to entry time of the new state
        stateEntryTimes[currentState] = now;
    }

public:
    // Function to log state durations
    void LogStateDurations() {
        for (const auto& duration_entry : stateDurations) {
            std::string stateName;
            switch (duration_entry.first) {
                case AIState::Idle: stateName = "Idle"; break;
                case AIState::Patrol: stateName = "Patrol"; break;
                case AIState::Chase: stateName = "Chase"; break;
            }
            std::cout << "Time spent in " << stateName << ": " << duration_entry.second.count() << " seconds.\n";
        }
    }
};

// Example usage
int main() {
    AI ai;

    // Simulate game loop with input commands
    std::string commands[] = { "see_player", "lost_player", "patrol_complete", "see_player" };
    for (const auto& command : commands) {
        std::cout << "Input: " << command << "\n";
        ai.Input(command);
        ai.Update();
    }

    // Log the time spent in each state
    ai.LogStateDurations();

    return 0;
}
