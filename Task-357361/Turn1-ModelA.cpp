#include <iostream>

void vulnerableFunction(char *buffer, int length) {
    std::cout << "Enter some text: ";
    std::cin.getline(buffer, length + 1);
}

int main() {
    char buffer[10];
    vulnerableFunction(buffer, 10);

    // Normally, if buffer overflow occurs, this print statement might be overwritten.
    std::cout << "This line should print after user input." << std::endl;
    return 0;
}