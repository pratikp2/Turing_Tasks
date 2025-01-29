#include <iostream>
#include <string>
#include <vector>

// Base element interface
class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor* visitor) = 0;
    virtual int getVersion() const = 0;
};

// Version 1 element
class ElementV1 : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitElementV1(this);
    }

    int getVersion() const override {
        return 1;
    }
};

// Version 2 element: adds a new attribute
class ElementV2 : public Element {
public:
    ElementV2(const std::string& newAttribute) : newAttribute_(newAttribute) {}

    void accept(Visitor* visitor) override {
        visitor->visitElementV2(this);
    }

    int getVersion() const override {
        return 2;
    }

    const std::string& getNewAttribute() const {
        return newAttribute_;
    }

private:
    std::string newAttribute_;
};

// Base visitor interface
class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visitElementV1(ElementV1* element) = 0;

    // Added method for version 2
    virtual void visitElementV2(ElementV2* element) = 0;
};

// Concrete visitor that implements version 1 operations
class VisitorV1 : public Visitor {
public:
    void visitElementV1(ElementV1* element) override {
        std::cout << "Visiting ElementV1 with VisitorV1" << std::endl;
    }

    // Version 2 method is not implemented in VisitorV1,
    // which ensures backward compatibility.
    void visitElementV2(ElementV2* element) override {
        throw std::runtime_error("VisitorV1 does not support ElementV2");
    }
};

// Concrete visitor that implements operations for both versions
class VisitorV2 : public Visitor {
public:
    void visitElementV1(ElementV1* element) override {
        std::cout << "Visiting ElementV1 with VisitorV2" << std::endl;
    }

    void visitElementV2(ElementV2* element) override {
        std::cout << "Visiting ElementV2 with VisitorV2: " << element->getNewAttribute() << std::endl;
    }
};

// Dispatcher that handles versioned visits
class VisitorDispatcher {
public:
    void dispatch(Element* element, Visitor* visitor) {
        switch (element->getVersion()) {
            case 1:
                element->accept(visitor);
                break;
            case 2:
                if (auto elementV2 = dynamic_cast<ElementV2*>(element)) {
                    elementV2->accept(visitor);
                } else {
                    throw std::runtime_error("Invalid ElementV2 instance");
                }
                break;
            default:
                throw std::runtime_error("Unsupported element version");
        }
    }
};

int main() {
    std::vector<Element*> elements = {
        new ElementV1(),
        new ElementV2("New Attribute Value"),
    };

    VisitorV1 visitorV1;
    VisitorV2 visitorV2;

    VisitorDispatcher dispatcher;

    std::cout << "--- Using VisitorV1 ---" << std::endl;
    for (Element* element : elements) {
        try {
            dispatcher.dispatch(element, &visitorV1);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "\n--- Using VisitorV2 ---" << std::endl;
    for (Element* element : elements) {
        dispatcher.dispatch(element, &visitorV2);
    }

    for (Element* element : elements) {
        delete element;
    }

    return 0;
}
