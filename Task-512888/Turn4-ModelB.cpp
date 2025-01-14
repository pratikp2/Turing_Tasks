#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>

class WashingMachine {
public:
    enum State {
        Idle,
        Washing,
        Rinsing,
        Spinning,
        Complete,
        Error
    };

    WashingMachine() : currentState(Idle) {
        logFile.open("state_log.txt", std::ios::out | std::ios::app);
        if (!logFile) {
            std::cerr << "Error opening log file!" << std::endl;
        }
    }

    ~WashingMachine() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

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
                case Complete:
                    break;
                case Error:
                    stateError();
                    break;
                default:
                    break;
            }
        }
    }

private:
    State currentState;
    std::ofstream logFile;

    void logTransition(const std::string& stateName) {
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        logFile << "State Transition: " << stateName
                << " | Timestamp: " << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S")
                << std::endl;
    }

    void transitionState(State nextState) {
        if (isValidTransition(currentState, nextState)) {
            std::string stateName = stateToString(nextState);
            logTransition(stateName);
            currentState = nextState;
        } else {
            transitionState(Error);
        }
    }

    bool isValidTransition(State current, State next) {
        switch (current) {
            case Idle:
                return next == Washing;
            case Washing:
                return next == Rinsing;
            case Rinsing:
                return next == Spinning;
            case Spinning:
                return next == Complete;
            case Error:
                return false; // Error state can only be exited by resetting
            default:
                return false;
        }
    }

    std::string stateToString(State state) {
        switch (state) {
            case Idle: return "Idle";
            case Washing: return "Washing";
            case Rinsing: return "Rinsing";
            case Spinning: return "Spinning";
            case Complete: return "Complete";
            case Error: return "Error";
            default: return "Unknown";
        }
    }

    void stateIdle() {
        std::cout << "Washing Machine is idle.\n";
        std::cout << "Press 'S' to start washing.\n";
        char c;
        std::cin >> c;
        if (c == 'S' || c == 's') {
            transitionState(Washing);
        } else if (c == 'I' || c == 'i') {
            // Simulate invalid transition from Idle to Spinning
            transitionState(Spinning);
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

    void stateError() {
        std::cout << "An error has occurred. Machine in Error state.\n";
        std::cout << "Press 'R' to reset the machine.\n";
        char c;
        std::cin >> c;
        if (c == 'R' || c == 'r') {
            transitionState(Idle);
        }
    }
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
