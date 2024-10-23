#include <iostream>
#include <stdexcept>

int divide(int dividend, int divisor) {
    if (divisor == 0) {
        throw std::runtime_error("Division by zero is not allowed.");
    }
    return dividend / divisor;
}

int main() {
    int result;
    try {
        result = divide(10, 2);
        std::cout << "Result: " << result << std::endl;
        result = divide(10, 0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}