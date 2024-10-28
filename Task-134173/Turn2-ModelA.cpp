#include <iostream>
#include <string>
#include <stdexcept>

class SecureException : public std::exception {
public:
  SecureException(const std::string& errorCode, const std::string& userMessage, const std::string& logMessage) :
    errorCode_(errorCode), userMessage_(userMessage), logMessage_(logMessage) {}

  const char* what() const noexcept override {
    return userMessage_.c_str();
  }

  std::string getErrorCode() const {
    return errorCode_;
  }

  std::string getLogMessage() const {
    return logMessage_;
  }

private:
  std::string errorCode_;
  std::string userMessage_;
  std::string logMessage_;
};

void validateInput(const std::string& input) {
  // Simulate validation logic and throw an exception with appropriate messages
  if (input.find("sensitive") != std::string::npos) {
    throw SecureException(
      "ERR_INVALID_INPUT",
      "Invalid input data. Please check the provided information and try again.",
      "Invalid input contains sensitive data: " + input
    );
  }
}

int main() {
  std::string input;
  std::cout << "Enter some data: ";
  std::getline(std::cin, input);

  try {
    validateInput(input);
    std::cout << "Input valid!" << std::endl;
  } catch (const SecureException& e) {
    std::cout << "Error: " << e.what() << std::endl;

    // Log the error detail securely for analysis
    std::cerr << "Logged Error: " << e.getLogMessage() << std::endl;
    return 1;
  }
  return 0;
}