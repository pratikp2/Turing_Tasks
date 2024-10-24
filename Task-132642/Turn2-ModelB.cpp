#include <iostream>
#include <string>
#include <vector>
#include <zlib.h>

class FBVBackupSDK {
public:
    // Compress data using zlib (stream-based compression)
    std::vector<char> compress(const std::string& data) {
        std::vector<char> compressedData;

        int ret;
        z_stream strm;

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
        if (ret != Z_OK) {
            throw std::runtime_error("deflateInit failed");
        }

        strm.avail_in = static_cast<uInt>(data.size());
        strm.next_in = (Bytef*)data.data();

        // Increase the buffer size to avoid repeated reallocations
        int bufferSize = 1024;
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

        // Resize the vector to the actual compressed size
        compressedData.resize(strm.total_out);
        return compressedData;
    }

    // Decompress data using zlib (stream-based decompression)
    std::string decompress(const std::vector<char>& compressedData) {
        std::string decompressedData;

        int ret;
        z_stream strm;

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;