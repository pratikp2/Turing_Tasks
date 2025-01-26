#include <iostream>

// Define the AI states
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
        }
    }

    // Function to set AI state
    void SetState(AIState state) {
        currentState = state;
    }

private:
    AIState currentState;

    // State handling functions
    void HandleIdle() {
        std::cout << "AI is idle.\n";
        if (DetectPlayer()) {
            currentState = AIState::Chase;
        }
    }

    void HandlePatrol() {
        std::cout << "AI is patrolling.\n";
        if (DetectPlayer()) {
            currentState = AIState::Chase;
        } else if (PlayerOutOfSight()) {
            currentState = AIState::Idle;
        }
    }

    void HandleChase() {
        std::cout << "AI is chasing the player.\n";
        if (PlayerOutOfSight()) {
            currentState = AIState::Patrol;
        }
    }

    // Simulated conditions for state transitions
    bool DetectPlayer() {
        // Random chance of detecting player
        int randomValue = std::rand() % 2;
        return randomValue == 0; // Simple random detection
    }

    bool PlayerOutOfSight() {
        // Random chance of losing sight of the player
        int randomValue = std::rand() % 3;
        return randomValue == 0; // Simple random detection
    }
};

int main() {
    AI ai;
    std::srand(static_cast<unsigned>(std::time(0))); // Seed the random number generator

    for (int i = 0; i < 20; ++i) {
        ai.Update();
    }

    return 0;
}
