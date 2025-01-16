#include <iostream>
using namespace std;

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
        if (vendingMachine->dispenseProduct()) {
            vendingMachine->setState(new Dispensing);
        }
    }
};

class Dispensing : public State {
public:
    void handle(VendingMachine* vendingMachine) override {
        cout << "Vending machine is dispensing product..." << endl;
        if (vendingMachine->productDispensed()) {
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

    // Example of state-specific actions
    bool insertedCoin() {
        cout << "Coin inserted. Proceeding..." << endl;
        return true;
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

int main() {
    VendingMachine vendingMachine;

    while (true) {
        vendingMachine.process();
    }

    return 0;
}
