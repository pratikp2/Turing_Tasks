#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

// Forward declaration of VendingMachine
class VendingMachine;

// Define an interface for states
class State {
public:
    virtual ~State() = default;
    virtual void handle(VendingMachine* vendingMachine) = 0;
};

// Concrete states
class Idle : public State {
public:
    void handle(VendingMachine* vendingMachine) override;
};

class HasSelection : public State {
public:
    void handle(VendingMachine* vendingMachine) override;
};

class ProcessingPayment : public State {
public:
    void handle(VendingMachine* vendingMachine) override;
};

class Dispensing : public State {
public:
    void handle(VendingMachine* vendingMachine) override;
};

// Context class that uses the states
class VendingMachine {
private:
    State* currentState;

public:
    VendingMachine() {
        currentState = new Idle;  // Start in idle state
    }

    ~VendingMachine() {
        delete currentState;
    }

    void process() {
        currentState->handle(this);
    }

    void setState(State* newState) {
        delete currentState;
        currentState = newState;
    }

    // Example of state-specific actions
    bool insertedCoin() {
        cout << "Coin inserted. Proceeding..." << endl;
        return true;
    }

    bool validatePayment() {
        // Simulating payment validation logic
        cout << "Validating payment..." << endl;
        return true; // Assume payment validation is always successful
    }

    bool dispenseProduct() {
        cout << "Product dispensed. Grabbing product now!" << endl;
        return true; // Simulate successful dispensing
    }

    void productDispenseError() {
        cout << "Error during dispensing. Please try again." << endl;
    }

    bool productDispensed() {
        cout << "Product dispensing done. Back to idle." << endl;
        return true;
    }
};

// Implementation of concrete state methods
void Idle::handle(VendingMachine* vendingMachine) {
    cout << "Vending machine is idle. Waiting for selection." << endl;
    if (vendingMachine->insertedCoin()) {
        vendingMachine->setState(new HasSelection);
    }
}

void HasSelection::handle(VendingMachine* vendingMachine) {
    cout << "Vending machine has selection. Waiting for payment." << endl;
    if (vendingMachine->insertedCoin()) {
        vendingMachine->setState(new ProcessingPayment);
    }
}

void ProcessingPayment::handle(VendingMachine* vendingMachine) {
    cout << "Vending machine is processing payment..." << endl;
    if (vendingMachine->validatePayment()) {
        vendingMachine->setState(new Dispensing);
    } else {
        // Handle case where payment fails
        cout << "Payment validation failed. Returning to HasSelection state." << endl;
        vendingMachine->setState(new HasSelection);
    }
}

void Dispensing::handle(VendingMachine* vendingMachine) {
    cout << "Vending machine is dispensing product..." << endl;
    try {
        if (vendingMachine->dispenseProduct()) {
            // If dispensing was successful, transition back to Idle
            vendingMachine->setState(new Idle);
        } else {
            throw runtime_error("Dispense operation failed.");
        }
    } catch (const runtime_error& e) {
        // Handle dispensing error
        cout << e.what() << endl;
        vendingMachine->productDispenseError();
        // Optionally, transition to a safe state or retry
        vendingMachine->setState(new Idle); // Return to Idle
    }
}

int main() {
    VendingMachine vendingMachine;

    // Simulate one complete transaction
    vendingMachine.process(); // Idle -> HasSelection
    vendingMachine.process(); // HasSelection -> ProcessingPayment
    vendingMachine.process(); // ProcessingPayment -> Dispensing
    vendingMachine.process(); // Dispensing -> Idle

    return 0;
}
