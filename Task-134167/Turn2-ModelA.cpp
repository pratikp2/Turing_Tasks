#include <iostream>
#include <cstring>

bool checkBufferSize(const char* source, size_t destSize) {
  return strlen(source) < destSize;
}

int main() {
  const char* secretMessage = "This is a very secret message";
  const size_t bufferSize = 10;

  if (!checkBufferSize(secretMessage, bufferSize)) {
    std::cerr << "Error: Buffer overflow potential!" << std::endl;
    return 1; // Return non-zero to indicate an error
  }
  std::cout << "Buffer size check passed." << std::endl;
  return 0;
}