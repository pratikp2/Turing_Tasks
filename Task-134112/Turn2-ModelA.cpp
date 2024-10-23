#include <iostream>
#include <string>
#include <optional>
#include <stdexcept>

// Function that may fail and return an error message
std::expected<int, std::string> divide(int numerator, int denominator) {
  if (denominator == 0) {
    return std::err("Cannot divide by zero");
  }
  return numerator / denominator;
}

int main() {
  int numerator = 10;
  int denominator = 2;

  auto result = divide(numerator, denominator);

  if (result.has_value()) {
    std::cout << "Result: " << result.value() << std::endl;
  } else {
    std::cout << "Error: " << result.error() << std::endl;
  }
  return 0;
}