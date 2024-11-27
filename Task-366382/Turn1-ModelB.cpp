#include <iostream>
#include <list>

// Abstract Mediator class
class Mediator {
public:
    virtual void sendMessage(std::string message, std::string sender) = 0;
};

// Concrete Mediator class
class ConcreteMediator : public Mediator {
private:
    std::list<class Component*> components;

public:
    void registerComponent(Component* component) {
        components.push_back(component);
    }

    void sendMessage(std::string message, std::string sender) override {
        for (auto component : components) {
            if (component->getName() != sender) {
                component->receiveMessage(message, sender);
            }
        }
    }
};

// Abstract Component class
class Component {
protected:
    Mediator* mediator;
    std::string name;

public:
    Component(Mediator* mediator, std::string name)
        : mediator(mediator), name(name) {}

    std::string getName() const {
        return name;
    }

    virtual void sendMessage(std::string message) {
        mediator->sendMessage(message, name);
    }

    virtual void receiveMessage(std::string message, std::string sender) = 0;
};

// Concrete Component classes
class ConcreteComponent1 : public Component {
public:
    ConcreteComponent1(Mediator* mediator, std::string name)
        : Component(mediator, name) {}

    void sendMessage(std::string message) override {
        Component::sendMessage(message);
    }

    void receiveMessage(std::string message, std::string sender) override {
        std::cout << name << " received message from " << sender << ": " << message << std::endl;
    }
};

class ConcreteComponent2 : public Component {
public:
    ConcreteComponent2(Mediator* mediator, std::string name)
        : Component(mediator, name) {}

    void sendMessage(std::string message) override {
        Component::sendMessage(message);
    }

    void receiveMessage(std::string message, std::string sender) override {
        std::cout << name << " received message from " << sender << ": " << message << std::endl;
    }
};

int main() {
    ConcreteMediator* mediator = new ConcreteMediator();

    ConcreteComponent1* comp1 = new ConcreteComponent1(mediator, "Component1");
    ConcreteComponent2* comp2 = new ConcreteComponent2(mediator, "Component2");

    mediator->registerComponent(comp1);
    mediator->registerComponent(comp2);

    comp1->sendMessage("Hello, everyone!");
    comp2->sendMessage("Hi, Component1! How are you?");

    delete comp1;
    delete comp2;
    delete mediator;

    return 0;
}