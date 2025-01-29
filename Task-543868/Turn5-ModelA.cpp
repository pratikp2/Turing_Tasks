#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <functional>
#include <vector>

// Forward declare element types
struct ElementA;
struct ElementB;

// Define a variant type for our elements
using ElementVariant = std::variant<ElementA*, ElementB*>;

// Base Visitor Interface
struct IVisitor {
    virtual ~IVisitor() = default;
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;
};

// Concrete Visitor Implementations
struct VisitorV1 : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "VisitorV1: Visited ElementA\n";
    }
    void visit(ElementB* element) override {
        std::cout << "VisitorV1: Visited ElementB\n";
    }
};

struct VisitorV2 : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "VisitorV2: Visited ElementA\n";
    }
    void visit(ElementB* element) override {
        std::cout << "VisitorV2: Visited ElementB\n";
    }
};

// Element Classes
struct ElementA {
    void accept(IVisitor& visitor) { visitor.visit(this); }
};

struct ElementB {
    void accept(IVisitor& visitor) { visitor.visit(this); }
};

// Visitor Registry
class VisitorRegistry {
public:
    using VisitorFactory = std::function<std::unique_ptr<IVisitor>()>;

    // Register a visitor
    void registerVisitor(const std::string& name, VisitorFactory factory) {
        registry[name] = factory;
    }

    // Create a visitor by name
    std::unique_ptr<IVisitor> createVisitor(const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return it->second();
        }
        return nullptr; // or throw an exception
    }

private:
    std::map<std::string, VisitorFactory> registry;
};

// Load configuration and create a visitor
std::string loadConfiguration() {
    // This function simulates loading from a config file.
    // Let's say the desired visitor name is "VisitorV2".
    return "VisitorV2"; // You would typically load this from a config file.
}

// Client code demonstrating the registry-based visitor selection
int main() {
    // Create a visitor registry and register available visitors
    VisitorRegistry visitorRegistry;
    visitorRegistry.registerVisitor("VisitorV1", []() { return std::make_unique<VisitorV1>(); });
    visitorRegistry.registerVisitor("VisitorV2", []() { return std::make_unique<VisitorV2>(); });

    // Load the desired visitor based on configuration
    std::string visitorName = loadConfiguration();
    auto visitor = visitorRegistry.createVisitor(visitorName);
    
    // Create elements to be visited
    std::vector<ElementVariant> elements;
    elements.emplace_back(new ElementA());
    elements.emplace_back(new ElementB());

    // Use the selected visitor
    for (auto& element : elements) {
        std::visit([&visitor](auto* ptr) {
            if (ptr && visitor) {
                ptr->accept(*visitor);
            }
        }, element);
    }

    // Cleanup allocated memory
    for (auto& element : elements) {
        std::visit([](auto* ptr) { delete ptr; }, element);
    }

    return 0;
}
