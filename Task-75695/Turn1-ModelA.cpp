
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

// Simple encryption function for demonstration purposes
std::string encrypt(const std::string& text) {
  std::string encrypted;
  for (char ch : text) {
    encrypted.push_back(ch ^ 3); // XOR encryption with a simple key
  }
  return encrypted;
}

// Simple decryption function
std::string decrypt(const std::string& encrypted) {
  return encrypt(encrypted);
}

class AccessControl {
private:
  std::map<std::string, std::vector<std::string>> userPermissions;

public:
  bool validateInput(const std::string& input) {
    // Simple regex to check for valid characters (alphanumerics and underscores)
    const std::regex validInputRegex("^[a-zA-Z0-9_]+$");
    return std::regex_match(input, validInputRegex);
  }

  void addUser(const std::string& username, const std::vector<std::string>& permissions) {
    if (validateInput(username) && std::all_of(permissions.begin(), permissions.end(), [this](const std::string& perm){ return validateInput(perm); })) {
      userPermissions[username] = permissions;
    } else {
      std::cout << "Invalid input for username or permissions. User not added." << std::endl;
    }
  }

  bool authenticateUser(const std::string& username, const std::string& encryptedPassword) {
    // In a real application, this should be handled securely
    // For demonstration, we'll just check if the username exists
    return userPermissions.find(username) != userPermissions.end();
  }

  bool authorizeAccess(const std::string& username, const std::string& requiredPermission) {
    if (authenticateUser(username, "")) {
      const auto& permissions = userPermissions[username];
      return std::find(permissions.begin(), permissions.end(), requiredPermission) != permissions.end();
    }
    return false;
  }

  std::vector<std::string> getUserPermissions(const std::string& username) {
    if (authenticateUser(username, "")) {
      return userPermissions[username];
    }
    return {};
  }
};

int main() {
  AccessControl accessControl;

  // Adding users with permissions
  accessControl.addUser("alice", {"read", "write"});
  accessControl.addUser("bob", {"read"});

  std::string username, password;

  std::cout << "Username: ";
  std::getline(std::cin, username);

  std::cout << "Password: ";
  std::getline(std::cin, password);

  // Encrypt password for storage (in a real app, use a proper encryption library)
  std::string encryptedPassword = encrypt(password);

  if (accessControl.authenticateUser(username, encryptedPassword)) {
    std::cout << "User authenticated successfully!" << std::endl;

    std::string requiredPermission;
    std::cout << "Enter required permission: ";
    std::getline(std::cin, requiredPermission);

    if (accessControl.authorizeAccess(username, requiredPermission)) {
      std::cout << "Access granted!" << std::endl;
    } else {
      std::cout << "Access denied." << std::endl;
    }

    std::vector<std::string> permissions = accessControl.getUserPermissions(username);
    std::cout << "User Permissions: " << std::endl;
    for (const std::string& perm : permissions) {
      std::cout << perm << std::endl;
    }
  } else {
    std::cout << "Authentication failed." << std::endl;
  }

  return 0;
}
