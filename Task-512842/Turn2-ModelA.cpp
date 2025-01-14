#include <iostream>
#include <cmath>

// Define a macro for a logging function
#define LOG(msg) std::cout << "[LOG] " << msg << std::endl;

// Define a macro for squaring a number
#define SQUARE(x) ((x) * (x))

// Conditional compilation
#ifdef DEBUG
#define DEBUG_LOG(msg) LOG(msg)
#else
#define DEBUG_LOG(msg)
#endif

int main() {
    // Using LOG macro
    LOG("Starting the application...");

    double number = 5.0;

    // Using SQUARE macro
    double square = SQUARE(number);
    LOG("The square of " << number << " is " << square);

    // Debug logging
    DEBUG_LOG("This is a debug message only seen in DEBUG mode.");

    // Example of a potential pitfall
    int a = 5, b = 10;
    // This will not work as expected due to operator precedence
    int result = SQUARE(a + b); // Expands to (a + b) * (a + b) instead of a^2 + b^2

    LOG("Result of SQUARE(a + b): " << result);
    return 0;
}
