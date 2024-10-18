#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <zlib.h>
#include <vector>
#include <string>

void handleRequest(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    std::string content = "Some large content to be compressed";

    std::string acceptEncoding = request.get("Accept-Encoding", "");
    bool isCompressed = false;

    if (acceptEncoding.find("gzip") != std::string::npos) {
        // Compress content using gzip and set the appropriate headers
        std::vector<unsigned char> compressedContent;
        compressData(content, compressedContent); // Implement your compression function

        response.setContentLength(compressedContent.size());
        response.setChunkedTransferEncoding(false);
        response.set("Content-Encoding", "gzip");
        response.sendBuffer(&compressedContent[0], compressedContent.size());
        isCompressed = true;
    }

    if (!isCompressed) {
        // Send uncompressed content
        response.setContentLength(content.size());
        response.setChunkedTransferEncoding(false);
        response.sendBuffer(content.data(), content.size());
    }
}

// Compress data using zlib
int compressData(const std::string& input, std::vector<unsigned char>& output) {
    uLongf compressedSize = compressBound(input.size());
    output.resize(compressedSize);
    int result = compress(output.data(), &compressedSize, (const Bytef*)input.data(), input.size());
    if (result == Z_OK) {
        output.resize(compressedSize); // Resize to actual compressed size
    }
    return result;
}
