#include <iostream>
#include <fstream>
#include <zlib.h>

#define CHUNK_SIZE 1024

int main() {
    // Filenames for input and output
    const char* input_filename = "input.txt";
    const char* output_filename = "output.txt.gz";

    // Open input file in binary read mode
    std::ifstream in(input_filename, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Cannot open input file: " << input_filename << std::endl;
        return 1;
    }

    // Open output file in binary write mode
    std::ofstream out(output_filename, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Cannot open output file: " << output_filename << std::endl;
        return 1;
    }

    // Compress the data
    int ret;
    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 + 16, 9, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) {
        std::cerr << "deflateInit2 failed: " << ret << std::endl;
        return 1;
    }

    unsigned char inbuf[CHUNK_SIZE];
    unsigned char outbuf[CHUNK_SIZE];

    while (true) {
        strm.avail_in = in.readsome(reinterpret_cast<char*>(inbuf), CHUNK_SIZE);
        if (strm.avail_in == 0)
            break;

        strm.next_in = inbuf;

        while (strm.avail_in > 0) {
            strm.avail_out = CHUNK_SIZE;
            strm.next_out = outbuf;

            ret = deflate(&strm, Z_NO_FLUSH);
            if (ret != Z_OK) {
                std::cerr << "deflate failed: " << ret << std::endl;
                return 1;
            }

            out.write(reinterpret_cast<char*>(outbuf), CHUNK_SIZE - strm.avail_out);
        }
    }

    ret = deflateFlush(&strm);
    if (ret != Z_OK) {
        std::cerr << "deflateFlush failed: " << ret << std::endl;