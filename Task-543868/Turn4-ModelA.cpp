#include <iostream>
#include <variant>
#include <vector>
#include <memory>
#include <type_traits>

// Forward declare element types
struct ElementA;
struct ElementB;
struct ElementC; // New element type

// Define a variant type for our elements
using ElementVariant = std::variant<ElementA*, ElementB*, ElementC*>;

// Element Classes
struct ElementA {
    void accept(auto& visitor) { visitor.visit(this); }
};

struct ElementB {
    void accept(auto& visitor) { visitor.visit(this); }
};

// New Element type
struct ElementC {
    void accept(auto& visitor) { visitor.visit(this); }
};

// Base Visitor Interface
struct IVisitor {
    virtual ~IVisitor() = default;
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;

    // Provide a fallback for new types
    virtual void visit(ElementC* element) {
        std::cout << "Default handling for new ElementC in old visitor\n";
    }
};

// Older Visitor Implementation
struct OlderVisitor : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (Older Visitor)\n";
    }
    
    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (Older Visitor)\n";
    }
    
    // Intentionally no visit for ElementC
};

// Newer Visitor Implementation
struct NewerVisitor : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (Newer Visitor)\n";
    }

    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (Newer Visitor)\n";
    }

    void visit(ElementC* element) override {
        std::cout << "Visited ElementC (Newer Visitor)\n";
    }
};

// Client code demonstrating the usage of variant and the visitor pattern
int main() {
    std::vector<ElementVariant> elements;
    elements.emplace_back(new ElementA());
    elements.emplace_back(new ElementB());
    elements.emplace_back(new ElementC()); // Add ElementC, the new type

    OlderVisitor oldVisitor;
    NewerVisitor newVisitor;

    // Using OlderVisitor
    std::cout << "Using Older Visitor:\n";
    for (auto& element : elements) {
        std::visit([&oldVisitor](auto ptr) {
            if (ptr) {
                ptr->accept(oldVisitor);
            }
        }, element);
    }

    std::cout << "Using Newer Visitor:\n";
    // Using NewerVisitor
    for (auto& element : elements) {
        std::visit([&newVisitor](auto ptr) {
            if (ptr) {
                ptr->accept(newVisitor);
            }
        }, element);
    }

    // Cleanup allocated memory
    for (auto& element : elements) {
        std::visit([](auto ptr) { delete ptr; }, element);
    }

    return 0;
}
