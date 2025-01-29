#include <iostream>
#include <memory>
#include <type_traits>

// Forward declare our Element classes.
class ElementA;
class ElementB;

// Base Visitor class
class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void visit(ElementA* element) = 0;  // Visitor for ElementA
    virtual void visit(ElementB* element) = 0;  // Visitor for ElementB
};

// Versioned Visitor Interface
class IVersionedVisitor {
public:
    virtual ~IVersionedVisitor() = default;

    // Acts as a versioned interface which you can extend
    virtual void visitV1(ElementA* element) { std::cout << "Visited ElementA (v1)\n"; }
    virtual void visitV1(ElementB* element) { std::cout << "Visited ElementB (v1)\n"; }

    // Adding new methods while maintaining backward compatibility
    virtual void visitV2(ElementA* element) { std::cout << "Visited ElementA (v2)\n"; }
    virtual void visitV2(ElementB* element) { std::cout << "Visited ElementB (v2)\n"; }
};

// Element classes
class IElement {
public:
    virtual ~IElement() = default;
    virtual void accept(IVisitor* visitor) = 0;
};

class ElementA : public IElement {
public:
    void accept(IVisitor* visitor) override {
        visitor->visit(this); // Calls appropriate visit method
    }
};

class ElementB : public IElement {
public:
    void accept(IVisitor* visitor) override {
        visitor->visit(this); // Calls appropriate visit method
    }
};

// Concrete Visitor implementing the versioned interfaces
class ConcreteVisitor : public IVisitor, public IVersionedVisitor {
public:
    void visit(ElementA* element) override {
        // Calls the versioned visitor method depending on the version defined
        visitV2(element); // Switch between visitV1/visitV2 as needed
    }

    void visit(ElementB* element) override {
        visitV2(element);
    }
};

// Usage example
int main() {
    std::unique_ptr<IElement> elements[] = {
            std::make_unique<ElementA>(),
            std::make_unique<ElementB>()
    };

    ConcreteVisitor visitor;

    for (auto& element : elements) {
        element->accept(&visitor);
    }

    return 0;
}
