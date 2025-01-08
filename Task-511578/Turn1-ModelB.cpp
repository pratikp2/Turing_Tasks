#include <iostream>
#include <cstdlib> // For malloc
#include <cstring> // For strcpy

using namespace std;

// Function to demonstrate memory management in switch-case
void processCommand(int command) {
    char* data = nullptr;

    switch (command) {
        case 1: // Allocate memory and store some data
            data = (char*)malloc(100);
            if (data != nullptr) {
                strcpy(data, "This is some data");
            } else {
                cerr << "Memory allocation failed!" << endl;
                return;
            }
            break;
        case 2: // Process data (no memory allocation)
            cout << "Processing data..." << endl;
            break;
        default:
            cout << "Invalid command." << endl;
            break;
    }

    // Free the allocated memory (if applicable)
    if (data != nullptr) {
        free(data);
        data = nullptr;
    }
}

int main() {
    int command;

    do {
        cout << "Enter a command: ";
        cin >> command;
        processCommand(command);
    } while (command != 0);

    cout << "Program exiting..." << endl;
    return 0;
}
