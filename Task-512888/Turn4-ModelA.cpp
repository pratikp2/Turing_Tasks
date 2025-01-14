#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

class WashingMachine {
public:
    enum State {
        Idle,
        Washing,
        Rinsing,
        Spinning,
        Complete,
        Error // New error state
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
                case Error: // Handle error state
                    stateError();
                    break;
                default:
                    break;
            }
        }
        stateComplete();
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

    void logError(const std::string& errorMessage) {
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        
        logFile << "Error: " << errorMessage
                << " | Timestamp: " << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S")
                << std::endl;
    }

    void transitionState(State nextState) {
        if (isValidTransition(nextState)) {
            std::string stateName = stateToString(nextState);
            logTransition(stateName);
            currentState = nextState;
        } else {
            transitionState(Error); // Transition to Error state
        }
    }

    bool isValidTransition(State nextState) {
        // Define valid transitions
        switch (currentState) {
            case Idle:
                return nextState == Washing; // Valid transition from Idle to Washing
            case Washing:
                return nextState == Rinsing; // Valid transition from Washing to Rinsing
            case Rinsing:
                return nextState == Spinning; // Valid transition from Rinsing to Spinning
            case Spinning:
                return nextState == Complete; // Valid transition from Spinning to Complete
            default:
                return false; // Invalid transition for other cases
        }
    }

    std::string stateToString(State state) {
        switch (state) {
            case Idle: return "Idle";
            case Washing: return "Washing";
            case Rinsing: return "Rinsing";
            case Spinning: return "Spinning";
            case Complete: return "Complete";
            case Error: return "Error"; // String representation for Error state
            default: return "Unknown";
        }
    }

    void stateIdle() {
        std::cout << "Washing Machine is idle.\n";
        std::cout << "Press 'S' to start washing, or 'X' to trigger an invalid transition.\n";
        char c;
        std::cin >> c;
        if (c == 'S' || c == 's') {
            transitionState(Washing);
        } else if (c == 'X' || c == 'x') {
            transitionState(Rinsing); // Simulate invalid transition to Rinsing when in Idle
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
        std::cout << "An error occurred: Invalid state transition! Switching to error state.\n";
        logError("Invalid state transition detected.");
        // After handling the error, we might want to reset or halt. For this example, let's stay in Error state.
        char c;
        std::cout << "Press 'R' to return to Idle or 'Q' to quit.\n";
        std::cin >> c;
        if (c == 'R' || c == 'r') {
            currentState = Idle; // Reset to Idle state
            logTransition("Idle");
        } else if (c == 'Q' || c == 'q') {
            transitionState(Complete); // Transition to Complete to exit
        }
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
