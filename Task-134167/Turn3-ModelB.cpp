#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

int main() {
  try {
    // Generate a 256-bit secure key
    SecByteBlock key(32); // 32 bytes = 256 bits
    AutoSeededRandomPool rng;
    key.Randomize(rng);

    // Save the key to a file in hexadecimal format
    std::ofstream keyFile("secure_key.txt");
    StringSource(key, true, new HexEncoder(new FileSink(keyFile)));
    keyFile.close();

    std::cout << "Secure key generated successfully!" << std::endl;
  } catch (const CryptoPP::Exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}