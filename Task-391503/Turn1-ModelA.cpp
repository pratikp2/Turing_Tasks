#include <iostream>

// Define the State interface
class State {
public:
    virtual void operation() const = 0;
};

// Concrete states
class ConcreteStateA : public State {
public:
    void operation() const override {
        std::cout << "Executing operation in State A." << std::endl;
    }
};

class ConcreteStateB : public State {
public:
    void operation() const override {
        std::cout << "Executing operation in State B." << std::endl;
    }
};

// Context class
class Context {
private:
    State* state;

public:
    // Constructor
    Context(State* initialState) : state(initialState) {}

    // Destructor
    ~Context() {
        delete state;
    }

    // Accessor for the current state
    State* getState() const {
        return state;
    }

    // Method to set the current state
    void setState(State* newState) {
        delete state;
        state = newState;
    }

    // Delegate the operation to the current state
    void operation() const {
        state->operation();
    }
};

// The Client
int main() {
    // Create the initial state
    ConcreteStateA* stateA = new ConcreteStateA();
    Context* context = new Context(stateA);

    // Perform operations with the initial state
    std::cout << "Initial state: ";
    context->operation();  // Should print "Executing operation in State A."

    // Transition to another state
    ConcreteStateB* stateB = new ConcreteStateB();
    context->setState(stateB);

    // Perform operations with the new state
    std::cout << "State transitioned to State B: ";
    context->operation();  // Should print "Executing operation in State B."

    // Cleanup
    delete context;
    delete stateB;

    return 0;
}
