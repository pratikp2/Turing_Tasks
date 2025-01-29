#include <iostream>
#include <variant>
#include <vector>
#include <memory>
#include <type_traits>

// Forward declare Element types
struct ElementA;
struct ElementB;
struct ElementC; // Newly introduced element

using ElementVariant = std::variant<ElementA*, ElementB*, ElementC*>;

// Base Visitor Interface
struct IVisitor {
    virtual ~IVisitor() = default;
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;

    // Provide a default implementation for ElementC
    virtual void visit(ElementC* element) {
        std::cout << "Visited ElementC (default handling by older visitor)\n";
    }
};

// Versioned Visitor Implementation
struct ConcreteVisitorV2 : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (V2)\n";
    }

    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (V2)\n";
    }

    void visit(ElementC* element) override {
        std::cout << "Visited ElementC (V2)\n";
    }
};

// Client code demonstrating the usage of variant and the visitor pattern with fallback
int main() {
    std::vector<ElementVariant> elements;
    elements.emplace_back(new ElementA());
    elements.emplace_back(new ElementB());
    elements.emplace_back(new ElementC());

    IVisitor* visitor = new ConcreteVisitorV2(); // Using older visitor

    for (auto& element : elements) {
        std::visit([visitor](auto ptr) {
            if (ptr) {
                ptr->accept(*visitor);
            }
        }, element);
    }

    delete visitor;
    return 0;
}
