#include <iostream>

// Singleton class to manage device states
class DeviceManager {
public:
    static DeviceManager& getInstance() {
        static DeviceManager instance;
        return instance;
    }

    // Method to transition to a new state
    void transitionToState(State* newState) {
        if (currentState) {
            delete currentState; // Release the previous state
        }
        currentState = newState;
        if (currentState) {
            currentState->enter();
        }
    }

    // Method to perform an operation in the current state
    void performOperation() const {
        if (currentState) {
            currentState->handleOperation();
        } else {
            std::cout << "Device is not in any state." << std::endl;
        }
    }

    ~DeviceManager() {
        if (currentState) {
            delete currentState;
        }
    }

private:
    DeviceManager() = default;
    DeviceManager(const DeviceManager&) = delete;
    DeviceManager& operator=(const DeviceManager&) = delete;

    State* currentState = nullptr;
};

// Base State class
class State {
public:
    virtual void enter() = 0;
    virtual void handleOperation() const = 0;
    virtual ~State() = default;
};

// Concrete states
class OffState : public State {
public:
    void enter() override {
        std::cout << "Device is in OffState." << std::endl;
    }

    void handleOperation() const override {
        std::cout << "Device is Off: No operation allowed." << std::endl;
    }
};

class OnState : public State {
public:
    void enter() override {
        std::cout << "Device is in OnState." << std::endl;
    }

    void handleOperation() const override {
        std::cout << "Device is On: Performing operation." << std::endl;
    }
};

class SleepState : public State {
public:
    void enter() override {
        std::cout << "Device is in SleepState." << std::endl;
    }

    void handleOperation() const override {
        std::cout << "Device is Sleeping: No operation allowed." << std::endl;
    }
};

int main() {
    // Get the singleton instance
    DeviceManager& deviceManager = DeviceManager::getInstance();

    // Initialize the device in OffState
    deviceManager.transitionToState(new OffState);

    // Attempt to perform an operation
    deviceManager.performOperation();

    // Transition to OnState
    deviceManager.transitionToState(new OnState);

    // Perform an operation
    deviceManager.performOperation();

    // Transition to SleepState
    deviceManager.transitionToState(new SleepState);

    // Attempt to perform an operation
    deviceManager.performOperation();

    // Cleanup the device manager (destructor will handle state deletion)
    return 0;
}