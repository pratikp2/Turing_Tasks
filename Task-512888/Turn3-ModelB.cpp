#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
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
        logFile.open("washing_machine_log.txt");
        if (!logFile.is_open()) {
            std::cerr << "Error: Cannot open log file!\n";
        }
    }

    ~WashingMachine() {
        logFile.close();
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

    void logTransition(const std::string& toState, const std::string& transitionReason) {
        std::time_t now = std::time(0);
        std::tm* currentTime = std::localtime(&now);
        std::string timestamp = std::strftime("%Y-%m-%d %H:%M:%S", currentTime);

        logFile << timestamp << ": Transitioned from " << getStateName(currentState)
                << " to " << toState << " - " << transitionReason << std::endl;
    }

    std::string getStateName(State state) {
        switch (state) {
            case Idle:     return "Idle";
            case Washing:  return "Washing";
            case Rinsing:  return "Rinsing";
            case Spinning: return "Spinning";
            case Complete: return "Complete";
        }
        return "Unknown State";
    }

    void transitionState(State nextState, const std::string& transitionReason) {
        logTransition(getStateName(nextState), transitionReason);
        currentState = nextState;
    }

    void stateIdle() {
        std::cout << "Washing Machine is idle.\n";
        std::cout << "Press 'S' to start washing.\n";
        char c;
        std::cin >> c;
        if (c == 'S' || c == 's') {
            transitionState(Washing, "User started washing");
        }
    }

    void stateWashing() {
        std::cout << "Washing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate washing time
        transitionState(Rinsing, "Washing cycle completed");
    }

    void stateRinsing() {
        std::cout << "Rinsing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate rinsing time
        transitionState(Spinning, "Rinsing cycle completed");
    }

    void stateSpinning() {
        std::cout << "Spinning...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate spinning time
        transitionState(Complete, "Spinning cycle completed");
    }

    void stateComplete() {
        std::cout << "Washing process is complete.\n";
        logTransition("Complete", "Washing process ended");
    }
};

int main() {
    WashingMachine machine;
    machine.run();

    return 0;
}
