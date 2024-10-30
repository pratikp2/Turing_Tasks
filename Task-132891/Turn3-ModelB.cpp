#include <iostream>
#include <string>

// Original Class (MathOperations)
class MathOperations {
public:
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) { return a / b; }
};

// Logging Proxy Class
class LoggingProxy {
public:
    LoggingProxy(MathOperations& mathOps) : mathOps_(mathOps) {}

    // Proxy methods that delegate the calls to the original MathOperations methods
    template<typename RetType, typename... Args>
    RetType add(Args&&... args) {
        log("add", std::forward<Args>(args)...);
        return mathOps_.add(std::forward<Args>(args)...);
    }

    template<typename RetType, typename... Args>
    RetType subtract(Args&&... args) {
        log("subtract", std::forward<Args>(args)...);
        return mathOps_.subtract(std::forward<Args>(args)...);
    }

    // We can do the same for multiply and divide as well

private:
    void log(const std::string& funcName, const double& a, const double& b) {
        std::cout << "Log: " << funcName << "(" << a << ", " << b << ") -> ";
    }

    MathOperations& mathOps_;
};

// Using the LoggingProxy to interact with MathOperations
int main() {
    MathOperations mathOps;
    LoggingProxy logger(mathOps);

    double result = logger.add(10.0, 20.0);
    std::cout << result << std::endl;  // Output: Log: add(10, 20) -> 30

    result = logger.subtract(30.0, 15.0);
    std::cout << result << std::endl;  // Output: Log: subtract(30, 15) -> 15
    return 0;
} 