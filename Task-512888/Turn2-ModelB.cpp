#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class WashingMachine {
public:
    enum State {
        Idle,
        Washing,
        Rinsing,
        Spinning,
        Complete
    };

    WashingMachine() : currentState(Idle) {}

    void run() {
        while (currentState != Complete) {
            handleCurrentState();
        }
        stateComplete();
    }

private:
    State currentState;

    void transitionState(State nextState) {
        currentState = nextState;
    }

    void handleCurrentState() {
        switch (currentState) {
            case Idle:
                stateIdle();
                break;
            case Washing:
                stateWashing();
                break;
            case Rinsing:
                stateRinsing();
                break;
            case Spinning:
                stateSpinning();
                break;
            default:
                std::cerr << "Invalid state: " << static_cast<int>(currentState) << std::endl;
                break;
        }
    }

    // State handlers remain the same...
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
