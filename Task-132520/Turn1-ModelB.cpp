#include <iostream>
#include <string>
#include <zlib.h>
#include <zmq.hpp>

int main() {
  // Create a ZeroMQ context
  zmq::context_t context(1);

  // Create a ZeroMQ socket
  zmq::socket_t socket(context, ZMQ_REQ);

  // Connect to the server
  socket.connect("tcp://localhost:5555");

  // Define the message to be sent
  std::string message = "Hello, world!";

  // Compress the message using Zlib
  int level = Z_BEST_COMPRESSION;
  int ret;
  z_stream strm;

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;

  ret = deflateInit(&strm, level);
  if (ret != Z_OK) {
    std::cerr << "Error initializing Zlib: " << ret << std::endl;
    return 1;
  }

  std::string compressed_data;
  int flush;

  do {
    strm.avail_in = message.size();
    strm.next_in = (Bytef *)message.data();

    compressed_data.resize(strm.total_out + 1024);
    strm.avail_out = compressed_data.size() - strm.total_out;
    strm.next_out = (Bytef *)compressed_data.data() + strm.total_out;

    flush = Z_FINISH;
    ret = deflate(&strm, flush);

    if (ret == Z_STREAM_END)
      break;
    if (ret != Z_OK) {
      std::cerr << "Error compressing data: " << ret << std::endl;
      deflateEnd(&strm);
      return 1;
    }
  } while (strm.avail_in > 0);

  deflateEnd(&strm);

  // Send the compressed message to the server
  socket.send(compressed_data.data(), compressed_data.size());

  // Receive the response from the server
  zmq::message_t response;
  socket.recv(&response);

  // Decompress the response using Zlib
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = response.size();
  strm.next_in = (Bytef *)response.data();

  std::string decompressed_response;

  do {
    decompressed_response.resize(strm.total_out + 1024);
    strm.avail_out = decompressed_response.size() - strm.total_out;
    strm.next_out = (Bytef *)decompressed_response.data() + strm.total_out;

    ret = inflate(&strm, Z_NO_FLUSH);