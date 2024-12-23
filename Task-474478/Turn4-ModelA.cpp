#include <iostream>
#include <bitset>
#include <memory>

// Implementor Interface
class BitwiseOperations {
public:
    virtual ~BitwiseOperations() = default;
    virtual std::bitset<8> performOperation(const std::bitset<8>& a, const std::bitset<8>& b) = 0;
};

// Concrete Implementor for AND operation
class AndOperation : public BitwiseOperations {
public:
    std::bitset<8> performOperation(const std::bitset<8>& a, const std::bitset<8>& b) override {
        return a & b; // Efficient AND operation
    }
};

// Concrete Implementor for OR operation
class OrOperation : public BitwiseOperations {
public:
    std::bitset<8> performOperation(const std::bitset<8>& a, const std::bitset<8>& b) override {
        return a | b; // Efficient OR operation
    }
};

// Abstraction
class BooleanConfigurator {
protected:
    std::unique_ptr<BitwiseOperations> operation;

public:
    BooleanConfigurator(std::unique_ptr<BitwiseOperations> op) : operation(std::move(op)) {}

    std::bitset<8> configure(const std::bitset<8>& a, const std::bitset<8>& b) {
        return operation->performOperation(a, b);
    }
};

// Client code
int main() {
    std::bitset<8> a("11001010"); // Example bit pattern
    std::bitset<8> b("10111001");

    // Using AND operation
    std::unique_ptr<BitwiseOperations> andOperation = std::make_unique<AndOperation>();
    BooleanConfigurator configurator(std::move(andOperation));
    std::bitset<8> resultAnd = configurator.configure(a, b);
    std::cout << "AND Result: " << resultAnd << std::endl;

    // Using OR operation
    std::unique_ptr<BitwiseOperations> orOperation = std::make_unique<OrOperation>();
    BooleanConfigurator configuratorOr(std::move(orOperation));
    std::bitset<8> resultOr = configuratorOr.configure(a, b);
    std::cout << "OR Result: " << resultOr << std::endl;

    return 0;
}
