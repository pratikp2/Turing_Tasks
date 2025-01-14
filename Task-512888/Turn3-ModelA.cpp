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
        Complete
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

    void transitionState(State nextState) {
        std::string stateName = stateToString(nextState);
        logTransition(stateName);
        currentState = nextState;
    }

    std::string stateToString(State state) {
        switch (state) {
            case Idle: return "Idle";
            case Washing: return "Washing";
            case Rinsing: return "Rinsing";
            case Spinning: return "Spinning";
            case Complete: return "Complete";
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
        logTransition("Complete");
    }
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
