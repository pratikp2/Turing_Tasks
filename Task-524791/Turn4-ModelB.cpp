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
    AI() : currentState(AIState::Idle) {}

    void Update() {
        switch (currentState) {
            case AIState::Idle:
                HandleIdle();
                break;

            case AIState::Patrol:
                HandlePatrol();
                break;

            case AIState::Chase:
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

private:
    AIState currentState;

    // Use chrono for timing
    std::chrono::high_resolution_clock::time_point stateEntryTime;

    // Unordered map to store time spent in each state
    std::unordered_map<AIState, std::chrono::duration<double, std::milli>> timeInState;

    void HandleIdle() {
        std::cout << "AI is currently idle.\n";
        LogStateEntry();

        if (ShouldStartPatrolling()) {
            SetState(AIState::Patrol);
        }
    }

    void HandlePatrol() {
        std::cout << "AI is patrolling.\n";
        LogStateEntry();

        if (DetectPlayer()) {
            SetState(AIState::Chase);
        }
    }

    void HandleChase() {
        std::cout << "AI is chasing the player!\n";
        LogStateEntry();

        if (PlayerOutOfSight()) {
            SetState(AIState::Patrol);
        }
    }

    void LogStateEntry() {
        // Record the time when entering a new state
        stateEntryTime = std::chrono::high_resolution_clock::now();
    }

    void LogStateExit() {
        // Calculate time spent in the current state when exiting
        auto exitTime = std::chrono::high_resolution_clock::now();
        auto timeSpent = exitTime - stateEntryTime;
        timeInState[currentState] += timeSpent;
        std::cout << "Time spent in " << GetStateName(currentState) << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpent).count() << " ms\n";
    }

    void SetState(AIState newState) {
        // Log exit time of the old state before entering the new state
        LogStateExit();
        currentState = newState;
    }

    std::string GetStateName(AIState state) const {
        switch (state) {
            case AIState::Idle:
                return "Idle";
            case AIState::Patrol:
                return "Patrol";
            case AIState::Chase:
                return "Chase";
            default:
                return "Unknown";
        }
    }

    bool DetectPlayer() {
        return false;
    }

    bool ShouldStartPatrolling() {
        return true;
    }

    bool PlayerOutOfSight() {
        return true;
    }

    // Display summary of time spent in each state at the end
    void DisplayStateTimes() {
        std::cout << "\n--- Summary of time spent in each state: ---\n";
        for (const auto& [state, time] : timeInState) {
            std::cout << GetStateName(state) << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " ms\n";
        }
    }
};

// Example usage
int main() {
    AI ai;

    std::string commands[] = { "see_player", "lost_player", "patrol_complete", "see_player", "see_player", "lost_player", "patrol_complete" };
    for (const auto& command : commands) {
        std::cout << "Input: " << command << "\n";
        ai.Input(command);
        ai.Update();
    }

    ai.DisplayStateTimes();

    return 0;
}
