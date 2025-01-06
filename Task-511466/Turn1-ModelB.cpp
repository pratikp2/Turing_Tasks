#include <stdexcept>

inline void divide(int dividend, int divisor, int& result) {
    if (divisor == 0) {
        throw std::runtime_error("Division by zero");
    }
    result = dividend / divisor;
}

void process() {
    int result;
    try {
        divide(10, 0, result);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    process();
    return 0;
}
