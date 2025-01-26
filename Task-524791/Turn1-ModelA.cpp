#include <iostream>

// Define the AI states as an enum for better readability
enum class AIState {
    Idle,
    Patrol,
    Chase
};

// AI class that manages behaviors
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

    void SetState(AIState newState) {
        currentState = newState;
    }

private:
    AIState currentState;

    void HandleIdle() {
        std::cout << "AI is currently idle.\n";
        // Check condition to change state, for example:
        if (DetectPlayer()) {
            SetState(AIState::Chase);
        } else {
            // Possible to stay idle longer or start patrolling
            // If patrol condition is met:
            if (ShouldStartPatrolling()) {
                SetState(AIState::Patrol);
            }
        }
    }

    void HandlePatrol() {
        std::cout << "AI is patrolling.\n";
        // Logic to patrol, move from point A to B

        // Check condition to change state
        if (DetectPlayer()) {
            SetState(AIState::Chase);
        }
    }

    void HandleChase() {
        std::cout << "AI is chasing the player.\n";
        // Logic to chase the player

        // Check condition to change state
        if (PlayerOutOfSight()) {
            SetState(AIState::Patrol);
        }
    }

    // Placeholder functions for example
    bool DetectPlayer() {
        // Add logic to detect the player
        return false; // Placeholder, replace with real detection logic
    }

    bool ShouldStartPatrolling() {
        // Logic to determine if AI should start patrolling
        return true; // Placeholder
    }

    bool PlayerOutOfSight() {
        // Logic to check if the player is out of sight
        return true; // Placeholder
    }
};

// Example usage
int main() {
    AI ai;

    // Simulate game loop
    for (int i = 0; i < 10; ++i) {
        ai.Update();
        // Simulate state change for testing
        if (i == 3) {
            ai.SetState(AIState::Patrol);
        }
        if (i == 6) {
            ai.SetState(AIState::Chase);
        }
    }

    return 0;
}
