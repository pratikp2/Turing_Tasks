#include <iostream>
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
        // Simulating dispensing logic with a random success rate
        cout << "Dispensing product..." << endl;
        if (rand() % 2 == 0) {
            cout << "Product dispensed successfully." << endl;
            return true;
        } else {
            cout << "Dispensing failed! Product not dispensed." << endl;
            return false;
        }
    }

    bool productDispensed() {
        cout << "Product dispensing done. Back to idle." << endl;
        return true;
    }

    // Error handling for failed dispensing, optionally go back to ProcessingPayment
    void dispensingFailed() {
        cout << "Dispensing failed. Attempting to restart payment processing..." << endl;
        setState(new ProcessingPayment);
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
        cout << "Payment validation failed. Returning to HasSelection state." << endl;
        vendingMachine->setState(new HasSelection);
    }
}

void Dispensing::handle(VendingMachine* vendingMachine) {
    cout << "Vending machine is dispensing product..." << endl;

    // Handle dispensing
    if (vendingMachine->dispenseProduct()) {
        // Transition to idle if dispensing is successful
        vendingMachine->setState(new Idle);
    } else {
        // Handle dispensing failure
        vendingMachine->dispensingFailed();
    }
}

int main() {
    VendingMachine vendingMachine;
    srand(static_cast<unsigned>(time(0))); // Seed random number generator for dispensing success

    vendingMachine.process(); // Idle -> HasSelection
    vendingMachine.process(); // HasSelection -> ProcessingPayment
    vendingMachine.process(); // ProcessingPayment -> Dispensing

    // We'll simulate multiple dispensing cycles to test handling
    for (int i = 0; i < 5; i++) {
        vendingMachine.process();
    }

    return 0;
}
