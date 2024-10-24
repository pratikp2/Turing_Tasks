#include <iostream>
#include <string>
#include <vector>
#include <zlib.h>

class FBVBackupSDK {
public:
   // Compress data using zlib
   std::vector<char> compress(const std::string& data) {
    std::vector<char> compressedData;

    int ret;
    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
      throw std::runtime_error("deflateInit failed");
    }

    strm.avail_in = static_cast<uInt>(data.size());
    strm.next_in = (Bytef*)data.data();

    int bufferSize = data.size() + data.size() / 100 + 12;
    compressedData.resize(bufferSize);

    do {
      strm.avail_out = static_cast<uInt>(compressedData.size() - strm.total_out);
      strm.next_out = (Bytef*)compressedData.data() + strm.total_out;
      ret = deflate(&strm, Z_FINISH);

      if (strm.total_out >= compressedData.size()) {
        compressedData.resize(compressedData.size() * 2);
      }
    } while (ret == Z_OK);

    deflateEnd(&strm);

    if (ret != Z_STREAM_END) {
      throw std::runtime_error("deflate failed");
    }

    compressedData.resize(strm.total_out);
    return compressedData;
   }

   // Decompress data using zlib
   std::string decompress(const std::vector<char>& compressedData) {
    std::string decompressedData;

    int ret;
    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK) {
      throw std::runtime_error("inflateInit failed");
    }

    strm.avail_in = static_cast<uInt>(compressedData.size());
    strm.next_in = (Bytef*)compressedData.data();

    int bufferSize = compressedData.size() * 10;
    decompressedData.resize(bufferSize);

    do {
      strm.avail_out = static_cast<uInt>(decompressedData.size() - strm.total_out);
      strm.next_out = (Bytef*)decompressedData.data() + strm.total_out;
      ret = inflate(&strm, Z_FINISH);

      if (strm.total_out >= decompressedData.size()) {
        decompressedData.resize(decompressedData.size() * 2);
      }
    } while (ret == Z_OK);

    inflateEnd(&strm);

    if (ret != Z_STREAM_END) {
      throw std::runtime_error("inflate failed");
    }

    decompressedData.resize(strm.total_out);
    return decompressedData;
   }
};

int main() {
   std::string data = "This is some sample data for compression testing";

   FBVBackupSDK sdk;
   try {
    auto compressedData = sdk.compress(data);
    std::cout << "Compressed data size: " << compressedData.size() << std::endl;

    auto decompressedData = sdk.decompress(compressedData);
    std::cout << "Decompressed data: " << decompressedData << std::endl;

    if (data != decompressedData) {
      std::cout << "Decompression failed!" << std::endl;
      return 1;
    }
    std::cout << "Compression and decompression successful!" << std::endl;
   } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
   }
   return 0;
}