#include <iostream>
#include <string>
#include <vector>
#include <zlib.h>

int main() {
  std::string inputData = "This is some sample data to be compressed.";

  // Compression with different levels
  for (int level = 1; level <= 9; level++) {
    std::vector<unsigned char> compressedData;
    int ret = compressData(inputData, compressedData, level);
    if (ret != Z_OK) {
      std::cerr << "Compression failed for level " << level << std::endl;
      return 1;
    }

    std::cout << "Compression level " << level << ": " << compressedData.size()
              << " bytes" << std::endl;
  }
  return 0;
}