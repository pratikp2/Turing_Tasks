#include <iostream>
#include <string>
#include <openssl/rand.h>
#include <openssl/evp.h>

int main() {
  // Generate a 256-bit symmetric encryption key
  unsigned char key[32];
  if (RAND_bytes(key, sizeof(key)) != 1) {
    std::cerr << "Error generating key" << std::endl;
    return 1;
  }

  // Store the key in a secure location (e.g., HSM or encrypted file)
  // For demonstration purposes, we'll just print it in hexadecimal
  for (int i = 0; i < sizeof(key); ++i) {
    printf("%02x", key[i]);
  }
  std::cout << std::endl;

  return 0;
}