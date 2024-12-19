#include <iostream>

enum State {
    STATE_0 = 1 << 0, // 1
    STATE_1 = 1 << 1, // 2
    STATE_2 = 1 << 2, // 4
    STATE_3 = 1 << 3  // 8
};

// Function to determine the next state
int getNextState(int currentState, int input) {
    // Transition table using bitwise logic
    switch (currentState) {
        case STATE_0:
            return (input == 0) ? STATE_1 : STATE_2; // 0 -> STATE_1, 1 -> STATE_2
        case STATE_1:
            return (input == 0) ? STATE_0 : STATE_3; // 0 -> STATE_0, 1 -> STATE_3
        case STATE_2:
            return (input == 0) ? STATE_3 : STATE_0; // 0 -> STATE_3, 1 -> STATE_0
        case STATE_3:
            return (input == 0) ? STATE_1 : STATE_2; // 0 -> STATE_1, 1 -> STATE_2
        default:
            return currentState; // Unknown state, do nothing
    }
}

int main() {
    int currentState = STATE_0; // Start at State 0
    int input;

    // Simulate some inputs
    for (int i = 0; i < 4; ++i) {
        std::cout << "Input (0 or 1): ";
        std::cin >> input; // Input should be 0 or 1
        currentState = getNextState(currentState, input);
        std::cout << "Next State: " << currentState << std::endl;
    }

    return 0;
}
