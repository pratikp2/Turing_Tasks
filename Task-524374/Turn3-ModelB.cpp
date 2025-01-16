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
    void handle(VendingMachine* vendingMachine) override {
        cout << "Vending machine is idle. Waiting for selection." << endl;
        if (vendingMachine->insertedCoin()) {
            vendingMachine->setState(new HasSelection);
        }
    }
};

class HasSelection : public State {
public:
    void handle(VendingMachine* vendingMachine) override {
        cout << "Vending machine has selection. Waiting for payment." << endl;
        if (vendingMachine->insertedCoin()) {
            vendingMachine->setState(new ProcessingPayment);
        }
    }
};

class ProcessingPayment : public State {
public:
    void handle(VendingMachine* vendingMachine) override {
        cout << "Vending machine is processing payment..." << endl;
        bool paymentSuccessful = vendingMachine->validatePayment();

        if (paymentSuccessful) {
            cout << "Payment validated successfully. Dispensing product..." << endl;
            vendingMachine->setState(new Dispensing);
        } else {
            cout << "Payment failed. Please insert correct amount." << endl;
            vendingMachine->setState(new HasSelection);
        }
    }
};

class Dispensing : public State {
public:
    void handle(VendingMachine* vendingMachine) override {
        cout << "Vending machine is dispensing product..." << endl;
        if (vendingMachine->dispenseProduct()) {
            vendingMachine->setState(new Idle);
        }
    }
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

    // Simulate payment validation
    bool validatePayment() {
        // You can add more complex logic here, like checking
        // for sufficient funds or calling external validation API.
        cout << "Validating payment..." << endl;
        // For demonstration, 70% success rate
        return (rand() % 100) < 70;
    }

    // Other methods remain the same
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    VendingMachine vendingMachine;

    while (true) {
        vendingMachine.process();
    }

    return 0;
}
