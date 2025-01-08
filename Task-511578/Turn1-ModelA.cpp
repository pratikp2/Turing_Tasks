#include <iostream>
#include <string>

enum Command {
    ADD, 
    DELETE, 
    MOD,
    EXIT
};

void executeCommand(Command cmd) {
    std::string* dynamicString = nullptr;

    switch (cmd) {
        case ADD:
            dynamicString = new std::string("Added item");
            std::cout << *dynamicString << std::endl;
            break;

        case DELETE:
            dynamicString = new std::string("Deleted item");
            std::cout << *dynamicString << std::endl;
            break;

        case MOD:
            dynamicString = new std::string("Modified item");
            std::cout << *dynamicString << std::endl;
            break;

        case EXIT:
            std::cout << "Exiting..." << std::endl;
            // Note: Default case contagion can happen here leading to potential undefined behavior
            break;

        default:
            std::cout << "Invalid Command" << std::endl;
            break;
    }

    // Here we may forget to release our dynamically allocated memory because of various control flow
    // if `case` statements don’t appropriately fall-through.
    delete dynamicString; // Leak is Believed to Occur on DEL, ADD or MOD cases if !EXIT
}

int main() {
    // Some usage scenarios - You can probably test this through some loop or event handling

    executeCommand(ADD);
    executeCommand(DELETE);
    executeCommand(MOD);
    executeCommand(EXIT);

    return 0;
}
