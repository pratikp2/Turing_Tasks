#include <iostream>
#include <string>
#include <map>
#include <memory>

// Forward declare Element types
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

// Versioned Visitor V1
struct VisitorV1 : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (V1)\n";
    }
    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (V1)\n";
    }
};

// Versioned Visitor V2
struct VisitorV2 : public IVisitor {
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (V2)\n";
    }
    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (V2)\n";
    }
};

// Element Classes
struct ElementA {
    void accept(auto& visitor) { visitor.visit(this); }
};

struct ElementB {
    void accept(auto& visitor) { visitor.visit(this); }
};

// Visitor Factory using Registry
class VisitorFactory {
private:
    std::map<std::string, std::function<std::unique_ptr<IVisitor>()>> visitorRegistry;

public:
    // Register a visitor
    template <typename T>
    void registerVisitor(const std::string& versionId) {
        visitorRegistry[versionId] = [&] {
            return std::make_unique<T>();
        };
    }

    // Create a visitor by version id
    std::unique_ptr<IVisitor> createVisitor(const std::string& versionId) {
        auto it = visitorRegistry.find(versionId);
        if (it == visitorRegistry.end()) {
            throw std::runtime_error("Visitor not found for version: " + versionId);
        }
        return it->second();
    }
};

// Example usage
int main() {
    VisitorFactory factory;

    factory.registerVisitor<VisitorV1>("V1");
    factory.registerVisitor<VisitorV2>("V2");

    ElementVariant elements[] = {
            std::make_unique<ElementA>(),
            std::make_unique<ElementB>()
    };

    auto visitorV1 = factory.createVisitor("V1");
    std::cout << "Using Visitor V1:\n";
    for (auto& element : elements) {
        std::visit([&visitorV1](auto ptr) {
            if (ptr) {
                ptr->accept(*visitorV1);
            }
        }, element);
    }

    auto visitorV2 = factory.createVisitor("V2");
    std::cout << "\nUsing Visitor V2:\n";
    for (auto& element : elements) {
        std::visit([&visitorV2](auto ptr) {
            if (ptr) {
                ptr->accept(*visitorV2);
            }
        }, element);
    }

    return 0;
}
