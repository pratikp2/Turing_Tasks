#include <iostream>
#include <string>
#include <vector>
#include <zlib.h>

int compressData(const std::string& input, std::vector<unsigned char>& output) {
  int ret;
  z_stream strm;

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
  if (ret != Z_OK) {
    std::cerr << "deflateInit failed: " << ret << std::endl;
    return ret;
  }

  strm.avail_in = static_cast<uInt>(input.size());
  strm.next_in = (Bytef*)input.data();

  int bufferSize = input.size() + 1000;
  output.resize(bufferSize);
  strm.avail_out = static_cast<uInt>(output.size());
  strm.next_out = output.data();

  ret = deflate(&strm, Z_FINISH);
  if (ret != Z_STREAM_END) {
    std::cerr << "deflate failed: " << ret << std::endl;
    deflateEnd(&strm);
    return ret;
  }

  deflateEnd(&strm);
  output.resize(strm.total_out);
  return Z_OK;
}

int decompressData(const std::vector<unsigned char>& input, std::string& output) {
  int ret;
  z_stream strm;

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = static_cast<uInt>(input.size());
  strm.next_in = (Bytef*)input.data();

  int bufferSize = input.size() * 10; // Assuming compression ratio of 10:1
  output.resize(bufferSize);
  strm.avail_out = static_cast<uInt>(output.size());
  strm.next_out = (Bytef*)output.data();

  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    std::cerr << "inflateInit failed: " << ret << std::endl;
    return ret;
  }

  ret = inflate(&strm, Z_FINISH);
  if (ret != Z_STREAM_END) {
    std::cerr << "inflate failed: " << ret << std::endl;
    inflateEnd(&strm);
    return ret;
  }

  inflateEnd(&strm);
  output.resize(strm.total_out);
  return Z_OK;
}

int main() {
  std::string inputData = "This is some sample data to be compressed.";

  std::vector<unsigned char> compressedData;
  int ret = compressData(inputData, compressedData);
  if (ret != Z_OK) {
    std::cerr << "Compression failed" << std::endl;
    return 1;
  }

  std::string decompressedData;
  ret = decompressData(compressedData, decompressedData);
  if (ret != Z_OK) {
    std::cerr << "Decompression failed" << std::endl;
    return 1;
  }

  std::cout << "Original data: " << inputData << std::endl;
  std::cout << "Compressed data size: " << compressedData.size() << " bytes" << std::endl;
  std::cout << "Decompressed data: " << decompressedData << std::endl;

  return 0;
}