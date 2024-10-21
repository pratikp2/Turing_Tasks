#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string data = "My name is John Doe, and I live at 123 Main Street. My phone number is (123) 456-7890.";
    std::regex regex_name("John Doe");
    std::regex regex_phone("(\\(\\d{3}\\)) \\d{3}-\\d{4}");

    std::string masked_data = std::regex_replace(data, regex_name, "XXX YYY");
    masked_data = std::regex_replace(masked_data, regex_phone, "(XXX) XXX-XXXX");

    std::cout << "Masked Data: " << masked_data << std::endl;

    return 0;
}