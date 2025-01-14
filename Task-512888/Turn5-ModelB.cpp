#include <iostream>
#include <fstream>
#include <string>
#include <map>
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
    
    // Mapping of states to valid transitions
    std::map<State, std::map<std::string, State>> transitions = {
        { Idle, { {"W", Washing}, {"R", Error} } },
        { Washing, { {"R", Rinsing} } },
        { Rinsing, { {"S", Spinning} } },
        { Spinning, { {"C", Complete} } },
        { Error, { {"R", Idle} } },
        { Complete, { } }
    };

    void logTransition(const std::string& stateName) {
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        logFile << "State Transition: " << stateName
                << " | Timestamp: " << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S")
                << std::endl;
    }

    void transitionState(State nextState) {
        if (isValidTransition(nextState)) {
            std::string stateName = stateToString(nextState);
            logTransition(stateName);
            currentState = nextState;
        } else {
            std::cout << "Invalid state transition. Machine will remain in current state." << std::endl;
        }
    }

    bool isValidTransition(State nextState) {
        auto it = transitions.find(currentState);
        if (it != transitions.end() && it->second.count(stateToString(nextState)) > 0) {
            return true;
        }
        return false;
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
        showMenu();
        std::string choice;
        std::cin >> choice;
        if (choice == "W") {
            transitionState(Washing);
        } else if (choice == "R") {
            transitionState(Rinsing);
        }
    }

    void stateWashing() {
        std::cout << "Washing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate washing time
        showMenu();
        std::string choice;
        std::cin >> choice;
        if (choice == "R") {
            transitionState(Rinsing);
        }
    }

    void stateRinsing() {
        std::cout << "Rinsing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate rinsing time
        showMenu();
        std::string choice;
        std::cin >> choice;
        if (choice == "S") {
            transitionState(Spinning);
        }
    }

    void stateSpinning() {
        std::cout << "Spinning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate spinning time
        showMenu();
        std::string choice;
        std::cin >> choice;
        if (choice == "C") {
            transitionState(Complete);
        }
    }

    void stateError() {
        std::cout << "An error has occurred. Machine in Error state.\n";
        showMenu();
        std::string choice;
        std::cin >> choice;
        if (choice == "R") {
            transitionState(Idle);
        }
    }

    void showMenu() {
        std::cout << "Available Transitions:\n";
        auto it = transitions.find(currentState);
        if (it != transitions.end()) {
            for (const auto& [command, nextState] : it->second) {
                std::cout << "\t" << command << ": " << stateToString(nextState) << std::endl;
            }
        }
        std::cout << "Please enter your choice:\n";
    }
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
