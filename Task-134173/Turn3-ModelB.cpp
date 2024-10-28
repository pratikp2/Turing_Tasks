#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>

// Define user roles
enum class UserRole {
  ADMIN,
  USER,
  GUEST
};

// Custom exception class for secure error handling
class SecureException : public std::exception {
public:
  SecureException(const std::string& errorCode, const UserRole& userRole) : errorCode_(errorCode), userRole_(userRole) {}
  const char* what() const noexcept override {
    return getErrorMessage().c_str();
  }
  std::string getErrorCode() const {
    return errorCode_;
  }
  UserRole getUserRole() const {
    return userRole_;
  }

private:
  std::string getErrorMessage() const {
    // Define error message templates for different user roles
    const std::unordered_map<std::string, std::unordered_map<UserRole, std::string>> errorMessageTemplates = {
      {"ERR_INVALID_INPUT", {
        {UserRole::ADMIN, "Invalid input data: [DETAILS]. Please check the provided information and try again."},
        {UserRole::USER, "Invalid input data. Please check the provided information and try again."},
        {UserRole::GUEST, "Invalid input data. Please correct and try again."}
      }},
      {"ERR_DATA_PROCESSING", {
        {UserRole::ADMIN, "An error occurred during data processing: [DETAILS]. Please contact support for assistance."},
        {UserRole::USER, "An error occurred during data processing. Please try again later."},
        {UserRole::GUEST, "An error occurred. Please try again later."}
      }}
    };

    // Get the appropriate error message template based on the error code and user role
    auto it = errorMessageTemplates.find(errorCode_);
    if (it != errorMessageTemplates.end()) {
      auto roleIt = it->second.find(userRole_);
      if (roleIt != it->second.end()) {
        std::string message = roleIt->second;
        // Replace '[DETAILS]' with actual error details (if available and safe to disclose for the user role)
        // For example, you can use logMessage_ (as shown in the previous code snippet) for ADMIN role.
        return message;
      }
    }

    // Default to a generic error message for unknown error codes or user roles
    return "An unknown error occurred.";
  }

  std::string errorCode_;
  UserRole userRole_;
};

void someFunctionThatMayFail(const UserRole& userRole) {
  // Simulate a failure condition and throw a SecureException
  throw SecureException("ERR_INVALID_INPUT", userRole);
}

int main() {
  try {
    someFunctionThatMayFail(UserRole::ADMIN);
  } catch (const SecureException& e) {
    // Handle the error securely
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
