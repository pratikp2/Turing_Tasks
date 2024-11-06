#include <iostream>
#include <string>

// Obfuscated variable names
int _secretNumber = 42;
std::string __encryptedData = "Uryyb, jbeyq vf n pnpur vf n yvzo kqqv jnagf.";

// Obfuscated function name
void _decodeAndPrintMessage() {
	for (char& c : __encryptedData) {
		c = static_cast<char>(c - 7);
	}
	std::cout << "Decoded message: " << __encryptedData << std::endl;
}

int main() {

	int* ptr = &_secretNumber;
	*ptr = *ptr * 2;

	std::cout << "Obfuscated number: " << _secretNumber << std::endl;

	_decodeAndPrintMessage();

	return 0;
}