#include <iostream>
#include <cstring>
#include <stdexcept>

void copyString(char* destination, size_t destSize, const char* source) {
  if (strlen(source) >= destSize) {
    throw std::length_error("Buffer is too small");
  }
  strcpy(destination, source);
}

int main() {
  const char* secretMessage = "This is a very secret message";
  const size_t bufferSize = 100;
  char* smallBuffer = new char[bufferSize]; // Allocate memory with the correct size

  try {
    copyString(smallBuffer, bufferSize, secretMessage);
    std::cout << "Copied Message: " << smallBuffer << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  delete[] smallBuffer; // Remember to free the allocated memory
  return 0;
}