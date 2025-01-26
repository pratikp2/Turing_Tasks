#include <iostream>
#include <string>

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

    void HandleIdle() {
        std::cout << "AI is currently idle.\n";
        // Logic for idle behavior, such as waiting or looking around

        // Example condition to transition to patrol (for demonstration only)
        if (ShouldStartPatrolling()) {
            std::cout << "AI decides to patrol.\n";
            SetState(AIState::Patrol);
        }
    }

    void HandlePatrol() {
        std::cout << "AI is patrolling.\n";
        // Logic for patrolling, e.g., moving between waypoints

        // Example condition to transition to chase
        if (DetectPlayer()) {
            std::cout << "AI sees the player!\n";
            SetState(AIState::Chase);
        }
    }

    void HandleChase() {
        std::cout << "AI is chasing the player!\n";
        // Logic for chasing the player

        // Example condition for losing sight of the player
        if (PlayerOutOfSight()) {
            std::cout << "AI lost sight of the player and will patrol now.\n";
            SetState(AIState::Patrol);
        }
    }

    // Placeholder functions for game logic
    bool DetectPlayer() {
        // Implement actual detection logic
        return false; // Placeholder: return true when player is detected
    }

    bool ShouldStartPatrolling() {
        // Implement logic to determine if the AI should start patrolling
        return true; // Placeholder: return true based on some condition
    }

    bool PlayerOutOfSight() {
        // Implement logic to check if the player is out of sight
        return true; // Placeholder: return true when the player is out of sight
    }

    void SetState(AIState newState) {
        currentState = newState;
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

    return 0;
}
