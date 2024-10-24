#include <lz4.h>

class FBVBackupSDK {
public:
   std::vector<char> compressLZ4(const std::string& data) {
    int compressedSize = LZ4_compressBound(data.size());
    std::vector<char> compressedData(compressedSize);

    int result = LZ4_compress_default((const char*)data.data(), compressedData.data(), data.size(), compressedSize);
    if (result <= 0) {
      throw std::runtime_error("LZ4 compression failed");
    }

    compressedData.resize(result);
    return compressedData;
   }

   std::string decompressLZ4(const std::vector<char>& compressedData) {
    int decompressedSize = LZ4_decompress_safe((const char*)compressedData.data(), nullptr, 0, compressedData.size());
    std::string decompressedData(decompressedSize, '\0');

    int result = LZ4_decompress_safe((const char*)compressedData.data(), (char*)decompressedData.data(), decompressedSize, compressedData.size());
    if (result != decompressedSize) {
      throw std::runtime_error("LZ4 decompression failed");
    }

    return decompressedData;
   }
};