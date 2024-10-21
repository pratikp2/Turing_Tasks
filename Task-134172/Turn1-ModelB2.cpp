#include <iostream>
#include <string>
#include <functional>

int main() {
    std::string data = "My name is John Doe, and I live at 123 Main Street. My phone number is (123) 456-7890.";
    std::hash<std::string> hash_function;
    size_t hash_value = hash_function(data);

    std::cout << "Hash Value: " << hash_value << std::endl;

    return 0;
}