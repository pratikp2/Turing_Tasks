#include <iostream>

// Inline function with a single definition in the header
inline void printMessage() {
    std::cout << "Hello from inline printMessage!" << std::endl;
}

// Variadic inline template function
template <typename... Args>
inline void printArgs(Args&&... args) {
    ((std::cout << args << " ", ++args), ...);
    std::cout << std::endl;
}

// Violates ODR: Multiple definitions of printMessage
// void printMessage() {
//     std::cout << "Violation of ODR!" << std::endl;
// }

int main() {
    printMessage();        // Uses the single defined inline function

    printArgs(1, 2.3, "three");   // Generates specialized version with int, double, const char*
    printArgs("Hello", 42);     // Generates specialized version with const char*, int

    return 0;
}
