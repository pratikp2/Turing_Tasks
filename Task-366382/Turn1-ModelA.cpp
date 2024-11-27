#include <iostream>

// Mediator interface
class Mediator {
public:
    virtual void relayMessage(const std::string& message, Component* sender) = 0;
};

// Concrete Mediator implementation
class ConcreteMediator : public Mediator {
public:
    void relayMessage(const std::string& message, Component* sender) override {
        for (const auto& component : components) {
            if (component != sender) {
                component->receiveMessage(message);
            }
        }
    }

    void addComponent(Component* component) {
        components.push_back(component);
    }

    void removeComponent(Component* component) {
        components.erase(std::remove_if(components.begin(), components.end(), [component](Component* c) {
            return c == component;
        }), components.end());
    }

private:
    std::vector<Component*> components;
};

// Component interface
class Component {
public:
    virtual void receiveMessage(const std::string& message) = 0;
    void setMediator(Mediator* mediator) {
        this->mediator = mediator;
    }

protected:
    Mediator* mediator;
};

// Concrete Components
class Workstation : public Component {
public:
    Workstation(const std::string& name) : name(name) {}

    void receiveMessage(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
    }

    void sendMessage(const std::string& message) {
        if (mediator != nullptr) {
            mediator->relayMessage(message, this);
        } else {
            std::cout << name << " cannot send message: no mediator set." << std::endl;
        }
    }

private:
    std::string name;
};

class Printer : public Component {
public:
    Printer(const std::string& name) : name(name) {}

    void receiveMessage(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
    }

    void sendMessage(const std::string& message) {
        if (mediator != nullptr) {
            mediator->relayMessage(message, this);
        } else {
            std::cout << name << " cannot send message: no mediator set." << std::endl;
        }
    }

private:
    std::string name;
};

// Main function to demonstrate the Mediator Pattern
int main() {
    Mediator* mediator = new ConcreteMediator();

    Workstation* workstation1 = new Workstation("Workstation 1");
    Workstation* workstation2 = new Workstation("Workstation 2");
    Printer* printer = new Printer("Printer");

    workstation1->setMediator(mediator);
    workstation2->setMediator(mediator);
    printer->setMediator(mediator);

    mediator->addComponent(workstation1);
    mediator->addComponent(workstation2);
    mediator->addComponent(printer);

    workstation1->sendMessage("Hello, Workstation 2 and Printer!");
    printer->sendMessage("Document printed successfully!");

    mediator->removeComponent(workstation2);
    workstation2->setMediator(nullptr); // Note: Not required if unique_ptr is used for lifetime management
    workstation1->sendMessage("Hello, Printer!");

    delete workstation1;
    delete workstation2;
    delete printer;
    delete mediator;

    return 0;
}