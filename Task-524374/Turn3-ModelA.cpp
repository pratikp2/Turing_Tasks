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
class Idle : public State;
class HasSelection : public State;
class ProcessingPayment : public State;
class Dispensing : public State;

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
        cout << "Product dispensed. Processing payment complete." << endl;
        return true;
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
    // Encapsulating the payment processing logic within the state
    cout << "Vending machine is processing payment..." << endl;
    
    // Validate the payment; the logic is encapsulated within the context
    if (vendingMachine->validatePayment()) {
        // Transition to the Dispensing state if payment is successful
        vendingMachine->setState(new Dispensing);
    } else {
        // If validation fails, you could handle that logic here (e.g., return to HasSelection)
        cout << "Payment validation failed. Returning to HasSelection state." << endl;
        vendingMachine->setState(new HasSelection);
    }
}

void Dispensing::handle(VendingMachine* vendingMachine) {
    cout << "Vending machine is dispensing product..." << endl;
    if (vendingMachine->dispenseProduct()) {
        vendingMachine->setState(new Idle);
    }
}

int main() {
    VendingMachine vendingMachine;

    // Simulate the machine's operation
    vendingMachine.process(); // Idle -> HasSelection
    vendingMachine.process(); // HasSelection -> ProcessingPayment
    vendingMachine.process(); // ProcessingPayment -> Dispensing
    vendingMachine.process(); // Dispensing -> Idle

    return 0;
}
