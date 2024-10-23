#include <iostream>
#include <system_error>
#include <fstream>

int main() {
  const char* file_path = "example.txt";
  std::ifstream file(file_path);

  if (!file.is_open()) {
    std::error_code ec(static_cast<int>(file.failbit), std::system_category());
    throw std::system_error(ec, "Failed to open file: " + std::string(file_path));
  }

  std::string content;
  file.seekg(0, std::ios::end);
  content.reserve(file.tellg());
  file.seekg(0, std::ios::beg);

  file.read(&content[0], content.size());
  if (!file.good()) {
    std::error_code ec(static_cast<int>(file.failbit), std::system_category());
    throw std::system_error(ec, "Failed to read file: " + std::string(file_path));
  }

  std::cout << "File content: " << content << std::endl;
  file.close();
  return 0;
}