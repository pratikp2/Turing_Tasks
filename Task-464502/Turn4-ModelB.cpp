// Example: Missing error state
int getNextState(int currentState, int input) {
    // ...
}

int main() {
    int currentState = STATE_0;
    for (int i = 0; i < 100; ++i) {
        int input = getRandomInput();
        currentState = getNextState(currentState, input);
        // What if currentState becomes invalid?
    }
}
