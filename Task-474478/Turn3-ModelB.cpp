#include <iostream>
#include <memory>
#include <string>

// Common utility functions for bit manipulation
class BitUtils {
public:
    static int performAnd(int a, int b) {
        return a & b;
    }

    static int performOr(int a, int b) {
        return a | b;
    }
};

// Implementor Interface
class BitwiseOperations {
public:
    virtual ~BitwiseOperations() = default;
    virtual int performOperation(int a, int b) = 0;
};

// Concrete Implementor for AND operation using utility functions
class AndOperation : public BitwiseOperations {
public:
    int performOperation(int a, int b) override {
        return BitUtils::performAnd(a, b);
    }
};

// Concrete Implementor for OR operation using utility functions
class OrOperation : public BitwiseOperations {
public:
    int performOperation(int a, int b) override {
        return BitUtils::performOr(a, b);
    }
};

// Abstraction
class BooleanConfigurator {
protected:
    std::unique_ptr<BitwiseOperations> operation;

public:
    BooleanConfigurator(std::unique_ptr<BitwiseOperations> op) : operation(std::move(op)) {}

    int configure(int a, int b) {
        return operation->performOperation(a, b);
    }
};

// Client code
int main() {
    // Configure AND operation
    std::unique_ptr<BitwiseOperations> andOperation = std::make_unique<AndOperation>();
    BooleanConfigurator configurator(std::move(andOperation));
    int resultAnd = configurator.configure(5, 3);
    std::cout << "And: " << resultAnd << std::endl;

    // Configure OR operation
    std::unique_ptr<BitwiseOperations> orOperation = std::make_unique<OrOperation>();
    BooleanConfigurator configuratorOr(std::move(orOperation));
    int resultOr = configuratorOr.configure(5, 3);
    std::cout << "Or: " << resultOr << std::endl;

    return 0;
}
