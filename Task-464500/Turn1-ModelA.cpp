#include <iostream>
#include <string>

// Variadic template function
template<typename... Args>
inline void printArgs(const Args&... args) {
    (std::cout << ... << args) << '\n'; // Fold expression to unpack parameters
}

int main() {
    // Example usage
    printArgs(1, 2.5, "Hello, world!", std::string("Variadic template"));
    printArgs(42); // Can handle single argument as well

    return 0;
}
