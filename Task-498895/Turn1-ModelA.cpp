#include <iostream>
#include <vector>

class GameObject {
public:
    // Define possible states using bit flags
    enum State {
        IDLE     = 1 << 0, // 0001
        MOVING   = 1 << 1, // 0010
        JUMPING  = 1 << 2, // 0100
        ATTACKING = 1 << 3 // 1000
    };

    GameObject() : state(0) {}

    // Set a state using bitwise OR
    void setState(State s) {
        state |= s;
    }

    // Clear a state using bitwise AND and NOT
    void clearState(State s) {
        state &= ~s;
    }

    // Check for a specific state using bitwise AND
    bool isState(State s) const {
        return state & s;
    }

    void printStates() const {
        std::cout << "Current States: ";
        if (isState(IDLE))     std::cout << "IDLE ";
        if (isState(MOVING))   std::cout << "MOVING ";
        if (isState(JUMPING))  std::cout << "JUMPING ";
        if (isState(ATTACKING)) std::cout << "ATTACKING ";
        std::cout << std::endl;
    }

private:
    unsigned int state; // Bit field to store states
};

int main() {
    GameObject character;

    // Set character states
    character.setState(GameObject::IDLE);
    character.setState(GameObject::MOVING);
    character.printStates();

    // Change states
    character.clearState(GameObject::MOVING);
    character.setState(GameObject::JUMPING);
    character.printStates();

    // Check for specific states
    if (character.isState(GameObject::JUMPING)) {
        std::cout << "Character is jumping!" << std::endl;
    }

    // Simulating a frame update
    if (character.isState(GameObject::IDLE) && !character.isState(GameObject::JUMPING)) {
        std::cout << "Character is ready to move." << std::endl;
    }

    return 0;
}
