#include <iostream>
#include <variant>
#include <vector>
#include <memory>

// Forward declare Element types
struct ElementA;
struct ElementB;

// Define a variant type for our elements
using ElementVariant = std::variant<ElementA*, ElementB*>;

// Base Visitor Interface using concepts
template <typename T>
concept VisitorConcept = requires(T v, ElementVariant e) {
    { v.visit(std::get<ElementA*>(e)) } -> std::same_as<void>; // Must be callable
    { v.visit(std::get<ElementB*>(e)) } -> std::same_as<void>; // Must be callable
};

// Element Classes
struct ElementA {
    void accept(auto& visitor) { visitor.visit(this); }
};

struct ElementB {
    void accept(auto& visitor) { visitor.visit(this); }
};

// Base Visitor Interface
template <VisitorConcept V>
struct IVisitor {
    virtual ~IVisitor() = default;
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;
};

//// Versioned Visitor Implementation
struct ConcreteVisitor : IVisitor<ConcreteVisitor> {
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA\n";
    }
    
    void visit(ElementB* element) override {
        std::cout << "Visited ElementB\n";
    }
};

// Adapted Visitor Example for Version Handling
struct VisitorAdapter : IVisitor<VisitorAdapter> {
    IVisitor<ConcreteVisitor>* legacyVisitor;

    VisitorAdapter(IVisitor<ConcreteVisitor>* visitor) : legacyVisitor(visitor) {}

    void visit(ElementA* element) override {
        legacyVisitor->visit(element); // Delegate to the legacy visitor
    }

    void visit(ElementB* element) override {
        legacyVisitor->visit(element); // Delegate to the legacy visitor
    }
};

// Client code demonstrating the usage of variant and the visitor pattern
int main() {
    std::vector<ElementVariant> elements;
    elements.emplace_back(new ElementA());
    elements.emplace_back(new ElementB());

    ConcreteVisitor visitor;

    for (auto& element : elements) {
        std::visit([&visitor](auto ptr) {
            if(ptr) { 
                ptr->accept(visitor); 
            }
        }, element);
    }

    return 0;
}
