#include <iostream>
#include <stdexcept>

class DivideByZeroException : public std::runtime_error {
public:
  DivideByZeroException() : std::runtime_error("Cannot divide by zero") {}
};

double divide(double dividend, double divisor) {
  if (divisor == 0) {
    throw DivideByZeroException();
  }
  return dividend / divisor;
}

int main() {
  double result;
  try {
    result = divide(10.0, 0.0);
    std::cout << "Result: " << result << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}