#include <iostream>
#include <memory>

// Implementor Interface
class BitwiseOperations {
public:
    virtual ~BitwiseOperations() = default;
    virtual void performOperation(int a, int b) = 0;
};

// Concrete Implementor for AND operation
class AndOperation : public BitwiseOperations {
public:
    void performOperation(int a, int b) override {
        std::cout << "And: " << (a & b) << std::endl;
    }
};

// Concrete Implementor for OR operation
class OrOperation : public BitwiseOperations {
public:
    void performOperation(int a, int b) override {
        std::cout << "Or: " << (a | b) << std::endl;
    }
};

// Abstraction
class BooleanConfigurator {
protected:
    std::unique_ptr<BitwiseOperations> operation;

public:
    BooleanConfigurator(std::unique_ptr<BitwiseOperations> op) : operation(std::move(op)) {}

    virtual void configure(int a, int b) {
        operation->performOperation(a, b);
    }
};

// Refined Abstraction
class AdvancedBooleanConfigurator : public BooleanConfigurator {
public:
    AdvancedBooleanConfigurator(std::unique_ptr<BitwiseOperations> op)
        : BooleanConfigurator(std::move(op)) {}

    void configure(int a, int b) override {
        std::cout << "Configuring using Advanced Boolean Configurator:" << std::endl;
        BooleanConfigurator::configure(a, b);
    }
};

// Client code
int main() {
    // Configure AND operation
    std::unique_ptr<BitwiseOperations> andOperation = std::make_unique<AndOperation>();
    AdvancedBooleanConfigurator configurator(std::move(andOperation));
    configurator.configure(5, 3);  // Output: And: 1

    // Change to OR operation without altering the configurator
    std::unique_ptr<BitwiseOperations> orOperation = std::make_unique<OrOperation>();
    AdvancedBooleanConfigurator configuratorOr(std::move(orOperation));
    configuratorOr.configure(5, 3);  // Output: Or: 7

    return 0;
}
