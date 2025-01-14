#include <iostream>
using namespace std;

enum class WashingMachineState {
    Idle,
    Washing,
    Rinsing,
    Spinning,
    Complete
};

class WashingMachine {
private:
    WashingMachineState currentState;

public:
    WashingMachine() : currentState(WashingMachineState::Idle) {}

    void transition(WashingMachineState nextState) {
        switch (currentState) {
            case WashingMachineState::Idle:
                switch (nextState) {
                    case WashingMachineState::Washing:
                        cout << "Starting washing cycle." << endl;
                        currentState = WashingMachineState::Washing;
                        break;
                    default:
                        cout << "Invalid transition from Idle state." << endl;
                }
                break;
            case WashingMachineState::Washing:
                switch (nextState) {
                    case WashingMachineState::Rinsing:
                        cout << "Washing completed. Starting rinsing cycle." << endl;
                        currentState = WashingMachineState::Rinsing;
                        break;
                    default:
                        cout << "Invalid transition from Washing state." << endl;
                }
                break;
            case WashingMachineState::Rinsing:
                switch (nextState) {
                    case WashingMachineState::Spinning:
                        cout << "Rinsing completed. Starting spinning cycle." << endl;
                        currentState = WashingMachineState::Spinning;
                        break;
                    default:
                        cout << "Invalid transition from Rinsing state." << endl;
                }
                break;
            case WashingMachineState::Spinning:
                switch (nextState) {
                    case WashingMachineState::Complete:
                        cout << "Spinning completed. Washing cycle finished." << endl;
                        currentState = WashingMachineState::Complete;
                        break;
                    default:
                        cout << "Invalid transition from Spinning state." << endl;
                }
                break;
            case WashingMachineState::Complete:
                cout << "Cannot transition from Complete state." << endl;
                break;
        }
    }

    WashingMachineState getCurrentState() {
        return currentState;
    }
};

int main() {
    WashingMachine washingMachine;

    cout << "Current state: " << washingMachine.getCurrentState() << endl;

    washingMachine.transition(WashingMachineState::Washing);
    washingMachine.transition(WashingMachineState::Rinsing);
    washingMachine.transition(WashingMachineState::Spinning);
    washingMachine.transition(WashingMachineState::Complete);

    cout << "Current state: " << washingMachine.getCurrentState() << endl;

    washingMachine.transition(WashingMachineState::Washing);  // Invalid transition

    return 0;
}
