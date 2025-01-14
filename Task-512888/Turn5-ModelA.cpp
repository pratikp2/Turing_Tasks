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
                return next == Washing || next == Error;
            case Washing:
                return next == Rinsing || next == Error;
            case Rinsing:
                return next == Spinning || next == Error;
            case Spinning:
                return next == Complete || next == Error;
            case Error:
                return next == Idle; // Can only reset to Idle from Error
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
        std::cout << "Select the next state:\n";
        std::cout << "1. Start Washing (W)\n";
        std::cout << "2. Go to Error (E)\n";
        
        char choice;
        std::cin >> choice;

        switch (choice) {
            case 'W': case 'w':
                transitionState(Washing);
                break;
            case 'E': case 'e':
                transitionState(Error);
                break;
            default:
                std::cout << "Invalid option. Staying in Idle state.\n";
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
        std::cout << "Select the next state:\n";
        std::cout << "1. Reset to Idle (R)\n";
        
        char choice;
        std::cin >> choice;

        switch (choice) {
            case 'R': case 'r':
                transitionState(Idle);
                break;
            default:
                std::cout << "Invalid option. Staying in Error state.\n";
        }
    }
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
