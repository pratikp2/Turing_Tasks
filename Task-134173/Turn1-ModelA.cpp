#include <iostream>
#include <string>
#include <stdexcept>

// Function to perform a sensitive operation (for demonstration purposes)
void performSensitiveOperation(const std::string& input) {
  if (input.empty()) {
    throw std::runtime_error("Invalid input provided.");
  }

  // Simulate a sensitive operation and throw an exception for an error
  if (input == "secret") {
    throw std::runtime_error("Unauthorized access attempted.");
  }

  std::cout << "Sensitive operation performed successfully for: " << input << std::endl;
}

int main() {
  try {
    std::string input;
    std::cout << "Enter input: ";
    std::getline(std::cin, input);

    performSensitiveOperation(input);

  } catch (const std::exception& e) {
    // Handle error securely
    std::string errorMessage = "An error occurred: ";
    errorMessage += e.what();

    // Display a generic error message to the user
    std::cerr << "Error: " << errorMessage << std::endl;
  }

  return 0;
}