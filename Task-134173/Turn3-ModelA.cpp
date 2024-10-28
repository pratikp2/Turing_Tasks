#include <iostream>
#include <string>
#include <stdexcept>
#include <map>

enum class UserRole {
  ADMIN,
  USER,
  GUEST
};

class SecureException : public std::exception {
public:
  SecureException(const std::string& errorCode, const std::string& userMessage, const std::string& logMessage, UserRole minVisibleRole) :
    errorCode_(errorCode), userMessage_(userMessage), logMessage_(logMessage), minVisibleRole_(minVisibleRole) {}

  const char* what() const noexcept override {
    return userMessage_.c_str();
  }

  std::string getErrorCode() const {
    return errorCode_;
  }

  std::string getLogMessage() const {
    return logMessage_;
  }

  UserRole getMinVisibleRole() const {
    return minVisibleRole_;
  }

private:
  std::string errorCode_;
  std::string userMessage_;
  std::string logMessage_;
  UserRole minVisibleRole_;
};

void validateInput(const std::string& input, UserRole userRole) {
  if (input.find("sensitive") != std::string::npos) {
    throw SecureException(
      "ERR_INVALID_INPUT",
      "Invalid input data. Please check and try again.",
      "Invalid input contains sensitive data: " + input,
      UserRole::ADMIN
    );
  }
  // Add more error checks and throw exceptions with appropriate roles
}

int main() {
  UserRole currentUserRole = UserRole::USER; // Replace this with the actual user role based on your application logic

  std::string input;
  std::cout << "Enter some data: ";
  std::getline(std::cin, input);

  try {
    validateInput(input, currentUserRole);
    std::cout << "Input valid!" << std::endl;
  } catch (const SecureException& e) {
    if (e.getMinVisibleRole() <= currentUserRole) {
      std::cout << "Error: " << e.what() << std::endl;
    } else {
      std::cout << "An error occurred. Please contact support." << std::endl;
    }

    // Log the error detail securely for analysis
    std::cerr << "Logged Error: " << e.getLogMessage() << std::endl;
    return 1;
  }
  return 0;
}