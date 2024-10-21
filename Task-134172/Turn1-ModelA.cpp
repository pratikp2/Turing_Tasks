
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

// Step 3: Overload the masking function for different data types
std::string maskString(const std::string& input, const std::string& mask = "*") {
   std::string maskedData = input;
   boost::algorithm::replace_all(maskedData, ".", mask);
   return maskedData;
}

int maskInteger(int input) {
   // Simple masking for integers: replace with zeroes
   return 0;
}

// Step 1: Use library function for masking
std::string maskCreditCard(const std::string& creditCardNumber) {
   const std::string mask = "*";
   return maskString(creditCardNumber, mask.substr(0, creditCardNumber.size() - 4)) + creditCardNumber.substr(creditCardNumber.size() - 4);
}

// Step 2: Design a masking function
template <typename T>
T maskData(const T& data) {
   // Default masking implementation for unsupported types
   static_assert(false, "Unsupported data type for masking");
}

// Partial specialization for std::string
template <>
std::string maskData<std::string>(const std::string& data) {
   return maskString(data);
}

// Partial specialization for int
template <>
int maskData<int>(const int& data) {
   return maskInteger(data);
}

int main() {
   std::string creditCard = "4111111111111111";
   std::cout << "Original Credit Card: " << creditCard << std::endl;
   std::cout << "Masked Credit Card: " << maskCreditCard(creditCard) << std::endl;

   std::string name = "Alice Johnson";
   std::cout << "Original Name: " << name << std::endl;
   std::cout << "Masked Name: " << maskData(name) << std::endl;

   int age = 30;
   std::cout << "Original Age: " << age << std::endl;
   std::cout << "Masked Age: " << maskData(age) << std::endl;
   return 0;
}