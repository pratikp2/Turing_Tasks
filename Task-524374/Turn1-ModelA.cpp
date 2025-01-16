#include <iostream>
#include <memory>

// Forward declaration of the VendingMachine class
class VendingMachine;

// State interface
class State {
public:
    virtual ~State() {}
    virtual void insertCoin(VendingMachine* machine) = 0;
    virtual void selectProduct(VendingMachine* machine) = 0;
    virtual void processPayment(VendingMachine* machine) = 0;
    virtual void dispenseProduct(VendingMachine* machine) = 0;
};

// Context class
class VendingMachine {
private:
    std::unique_ptr<State> currentState;

public:
    VendingMachine(std::unique_ptr<State> initialState) : currentState(std::move(initialState)) {}

    void setState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
    }

    void insertCoin() {
        currentState->insertCoin(this);
    }

    void selectProduct() {
        currentState->selectProduct(this);
    }

    void processPayment() {
        currentState->processPayment(this);
    }

    void dispenseProduct() {
        currentState->dispenseProduct(this);
    }
};

// Concrete State: Idle
class IdleState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Coin inserted." << std::endl;
        machine->setState(std::make_unique<HasSelectionState>());
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "Please insert a coin first." << std::endl;
    }

    void processPayment(VendingMachine* machine) override {
        std::cout << "Please insert a coin first." << std::endl;
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "Please insert a coin and select a product first." << std::endl;
    }
};

// Concrete State: HasSelection
class HasSelectionState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Coin already inserted." << std::endl;
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "Product selected." << std::endl;
        machine->setState(std::make_unique<ProcessingPaymentState>());
    }

    void processPayment(VendingMachine* machine) override {
        std::cout << "Please select a product first." << std::endl;
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "Please select a product first." << std::endl;
    }
};

// Concrete State: ProcessingPayment
class ProcessingPaymentState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Processing payment. Please wait..." << std::endl;
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "Already processing payment." << std::endl;
    }

    void processPayment(VendingMachine* machine) override {
        std::cout << "Payment processed successfully." << std::endl;
        machine->setState(std::make_unique<DispensingState>());
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "Payment not completed." << std::endl;
    }
};

// Concrete State: Dispensing
class DispensingState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Please wait, we are dispensing your product..." << std::endl;
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "Dispensing in progress." << std::endl;
    }

    void processPayment(VendingMachine* machine) override {
        std::cout << "Already processing payment." << std::endl;
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "Product has been dispensed. Thank you!" << std::endl;
        machine->setState(std::make_unique<IdleState>());
    }
};

// Main function to demonstrate the vending machine states
int main() {
    VendingMachine vendingMachine(std::make_unique<IdleState>());

    // Test the vending machine workflow
    vendingMachine.insertCoin();         // Coin inserted.
    vendingMachine.selectProduct();       // Product selected.
    vendingMachine.processPayment();      // Payment processed successfully.
    vendingMachine.dispenseProduct();     // Product has been dispensed. Thank you!

    return 0;
}
