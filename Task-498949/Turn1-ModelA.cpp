#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <cstring>

class CustomStreamBuffer : public std::streambuf {
public:
    CustomStreamBuffer(size_t bufferSize) {
        setp(buffer, buffer + bufferSize - 1); // Reserve the last character for null-terminator
    }

protected:
    // Buffer to hold data
    char *buffer = new char[bufferSize]; 
    size_t bufferSize;

    // Override overflow method for handling buffer flush
    int overflow(int c) override {
        sync(); // Flush current buffer before writing new character
        if (c != EOF) {
            *pptr() = static_cast<char>(c);
            pbump(1);
        }
        return c;
    }

    // Override sync method to flush the buffer to the output stream
    int sync() override {
        std::ofstream ofs("output.txt", std::ios::app);
        if (!ofs.is_open()) {
            return -1;
        }
        // Write the buffer to the file
        ofs.write(buffer, pptr() - pbase());
        // Reset the buffer pointers
        setp(buffer, buffer + bufferSize - 1);
        return 0;
    }

private:
    // Constructor parameter for buffer size
    CustomStreamBuffer(size_t size) : bufferSize(size) {
        buffer = new char[bufferSize];
        setp(buffer, buffer + bufferSize - 1); // Set pointers
    }

    ~CustomStreamBuffer() {
        sync(); // Flush remaining data before destruction
        delete[] buffer; // Free allocated memory
    }
};

int main() {
    const size_t bufferSize = 1024; // Example buffer size
    CustomStreamBuffer customBuffer(bufferSize);
    std::ostream customStream(&customBuffer);

    for (int i = 0; i < 10000; ++i) {
        customStream << "Writing line " << i << "\n";
    }

    // Flush any remaining data
    customStream.flush();

    return 0;
}
