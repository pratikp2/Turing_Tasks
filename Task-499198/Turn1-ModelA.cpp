#include <iostream>

enum State {
    STATE_INIT,
    STATE_RUNNING,
    STATE_STOPPED
};

class StateMachine {
private:
    State currentState;

    inline void enterInit() {
        std::cout << "Entering Init State\n";
        currentState = STATE_RUNNING;
    }

    inline void enterRunning() {
        std::cout << "Entering Running State\n";
        // Do something specific to running
    }

    inline void enterStopped() {
        std::cout << "Entering Stopped State\n";
        // Handle stopped state operations here
    }

public:
    StateMachine() : currentState(STATE_INIT) {
        enterInit();
    }

    void update() {
        switch (currentState) {
            case STATE_RUNNING:
                enterRunning();
                break;
            case STATE_STOPPED:
                enterStopped();
                break;
            default:
                break;
        }
    }

    void stop() {
        currentState = STATE_STOPPED;
    }
};

int main() {
    StateMachine sm;
    sm.update();
    sm.stop();
    sm.update();
    return 0;
}
