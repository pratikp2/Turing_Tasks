#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Forward declarations
class Mediator;
class Participant;

// Mediator Interface
class Mediator {
public:
    virtual void send(const std::string& message, Participant* sender) = 0;
};

// Participant Class
class Participant {
protected:
    Mediator* mediator;
    std::string name;

public:
    Participant(Mediator* mediator, const std::string& name) 
        : mediator(mediator), name(name) {}

    virtual void send(const std::string& message) {
        mediator->send(message, this);
    }

    virtual void receive(const std::string& message) {
        std::cout << name << " received: " << message << std::endl;
    }
};

// Concrete Mediator Class
class ChatMediator : public Mediator {
    std::vector<Participant*> participants;

public:
    void addParticipant(Participant* participant) {
        participants.push_back(participant);
    }

    void send(const std::string& message, Participant* sender) override {
        for(auto participant : participants) {
            if(participant != sender) {
                participant->receive(message);
            }
        }
    }
};

// Base Decorator Class
class MessageDecorator : public Participant {
protected:
    Participant* wrapped;

public:
    MessageDecorator(Mediator* mediator, Participant* participant) 
        : Participant(mediator, participant->name), wrapped(participant) {}

    void send(const std::string& message) override {
        wrapped->send(message);
    }
    
    void receive(const std::string& message) override {
        wrapped->receive(message);
    }
};

// Concrete Decorator for Logging
class LoggingDecorator : public MessageDecorator {
public:
    LoggingDecorator(Mediator* mediator, Participant* participant)
        : MessageDecorator(mediator, participant) {}

    void send(const std::string& message) override {
        std::cout << "Logging: " << name << " sends: " << message << std::endl;
        MessageDecorator::send(message);
    }
};

// Concrete Decorator for Formatting
class FormattingDecorator : public MessageDecorator {
public:
    FormattingDecorator(Mediator* mediator, Participant* participant)
        : MessageDecorator(mediator, participant) {}

    void send(const std::string& message) override {
        std::string formattedMessage = "[Formatted] " + message;
        MessageDecorator::send(formattedMessage);
    }
};

// Main Function to demonstrate behavior
int main() {
    ChatMediator mediator;

    Participant* john = new Participant(&mediator, "John");
    Participant* jane = new Participant(&mediator, "Jane");

    mediator.addParticipant(john);
    mediator.addParticipant(jane);

    // Using Decorators to enhance functionality
    Participant* loggedJohn = new LoggingDecorator(&mediator, john);
    Participant* formattedJane = new FormattingDecorator(&mediator, jane);

    loggedJohn->send("Hello Jane!");
    formattedJane->send("Hi John!");

    // Clean up
    delete john;
    delete jane;
    delete loggedJohn;
    delete formattedJane;

    return 0;
}
