#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

// Sample data structure for users
struct User {
  std::string username;
  std::unordered_set<std::string> roles;
};

// Sample data structure for resources
struct Resource {
  std::string name;
  std::vector<std::string> requiredRoles;
};

// Flattened access control matrix for efficient lookups
std::unordered_map<std::string, std::unordered_set<std::string>> accessControlMatrix;

// Function to initialize the access control matrix
void initializeAccessControlMatrix() {
  // ... (Populate the matrix based on your RBAC rules)
}

// Function to check if a user can access a resource
bool canAccessResource(const User& user, const Resource& resource) {
  // Check if the user's roles are a superset of the required roles for the resource
  return std::all_of(resource.requiredRoles.begin(), resource.requiredRoles.end(), [&user](const std::string& role) {
    return user.roles.find(role) != user.roles.end();
  });
}

int main() {
  // Initialize the access control matrix
  initializeAccessControlMatrix();

  User user = {"alice", {"Admin", "Editor"}};
  Resource resource = {"News Article 1", {"Editor", "Author"}};

  // Check if the user can access the resource using the optimized function
  if (canAccessResource(user, resource)) {
    std::cout << "User " << user.username << " can access resource " << resource.name << std::endl;
  } else {
    std::cout << "User " << user.username << " cannot access resource " << resource.name << std::endl;
  }

  return 0;
}