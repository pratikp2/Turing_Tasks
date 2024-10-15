

#include <iostream>
#include <string>
#include <regex>
#include <map>

// Simple class to represent a user
class User {
public:
    std::string username;
    std::string password;
    bool isAdmin;

    User(std::string username, std::string password, bool isAdmin) : username(username), password(password), isAdmin(isAdmin) {}
};

// Store user data in a map for demonstration purposes (In a real application, use a database)
std::map<std::string, User> users = {
    {"alice", User("alice", "password", false)},
    {"bob", User("bob", "secret", true)}
};

// Function to validate input using regex
bool validateInput(const std::string& input, const std::string& regexPattern) {
    std::regex regex(regexPattern);
    return std::regex_match(input, regex);
}

int main() {
    std::string username, password;

    // Input Validation: Username should be alphanumeric and limited to 20 characters
    std::cout << "Username: ";
    std::getline(std::cin, username);
    const std::string usernameRegex = "^[a-zA-Z0-9]{1,20}$";
    if (!validateInput(username, usernameRegex)) {
        std::cout << "Invalid username format. Access denied." << std::endl;
        return 1;
    }

    // Input Validation: Password should be at least 6 characters long
    std::cout << "Password: ";
    std::getline(std::cin, password);
    const std::string passwordRegex = "^.{6,}$";
    if (!validateInput(password, passwordRegex)) {
        std::cout << "Invalid password format. Access denied." << std::endl;
        return 1;
    }

    // Authentication
    auto it = users.find(username);
    if (it == users.end() || it->second.password != password) {