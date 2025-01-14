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
                    break;
            }
        }
        stateComplete();
    }

private:
    State currentState;

    void transitionState(State nextState) {
        currentState = nextState;
    }

    void stateIdle() {
        std::cout << "Washing Machine is idle.\n";
        std::cout << "Press 'S' to start washing.\n";
        char c;
        std::cin >> c;
        if (c == 'S' || c == 's') {
            transitionState(Washing);
        }
    }

    void stateWashing() {
        std::cout << "Washing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate washing time
        transitionState(Rinsing);
    }

    void stateRinsing() {
        std::cout << "Rinsing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate rinsing time
        transitionState(Spinning);
    }

    void stateSpinning() {
        std::cout << "Spinning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate spinning time
        transitionState(Complete);
    }

    void stateComplete() {
        std::cout << "Washing process is complete.\n";
    }
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
