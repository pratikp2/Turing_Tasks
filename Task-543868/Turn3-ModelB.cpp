#include <iostream>
#include <variant>
#include <utility>

class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void visit(ElementA* element) = 0;
    virtual void visit(ElementB* element) = 0;
};

class IVisitorV1 : public IVisitor {
public:
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (v1)\n";
    }

    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (v1)\n";
    }
};

class IVisitorV2 : public IVisitor {
public:
    void visit(ElementA* element) override {
        std::cout << "Visited ElementA (v2)\n";
    }

    void visit(ElementB* element) override {
        std::cout << "Visited ElementB (v2)\n";
    }
};

using VisitorVariant = std::variant<IVisitorV1, IVisitorV2>;

class IElement {
public:
    virtual ~IElement() = default;
    virtual void accept(VisitorVariant visitor) = 0;
};

class ElementA : public IElement {
public:
    void accept(VisitorVariant visitor) override {
        std::visit([&](const auto& v) {
            switch (v) {
                case IVisitorV1 v1: v1.visit(this); break;
                case IVisitorV2 v2: v2.visit(this); break;
            }
        }, visitor);
    }
};

class ElementB : public IElement {
public:
    void accept(VisitorVariant visitor) override {
        std::visit([&](const auto& v) {
            switch (v) {
                case IVisitorV1 v1: v1.visit(this); break;
                case IVisitorV2 v2: v2.visit(this); break;
            }
        }, visitor);
    }
};

int main() {
    std::unique_ptr<IElement> elements[] = {
        std::make_unique<ElementA>(),
        std::make_unique<ElementB>()
    };

    // Usage with V1 and V2 visitors
    VisitorVariant v1;
    VisitorVariant v2 = IVisitorV2();

    for (auto& element : elements) {
        element->accept(v1); // Use V1
        element->accept(v2); // Use V2
    }

    return 0;
}
