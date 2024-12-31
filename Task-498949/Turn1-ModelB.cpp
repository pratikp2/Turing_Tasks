#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

class CustomBuffer : public std::streambuf {
private:
    enum { BUFFER_SIZE = 8192 };
    char* buffer;
    int read_pos;
    int write_pos;
    int file_descriptor;

public:
    CustomBuffer(const char* filename) {
        buffer = new char[BUFFER_SIZE];
        read_pos = 0;
        write_pos = 0;
        file_descriptor = open(filename, O_RDONLY);
        if (file_descriptor == -1) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    ~CustomBuffer() {
        close(file_descriptor);
        delete[] buffer;
    }

protected:
    virtual std::streamsize xsgetn(char* s, std::streamsize n) override {
        while (read_pos == write_pos) {
            int bytes_read = read(file_descriptor, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                return bytes_read;
            }
            read_pos = 0;
            write_pos = bytes_read;
        }
        std::streamsize count = std::min(n, write_pos - read_pos);
        std::copy(buffer + read_pos, buffer + read_pos + count, s);
        read_pos += count;
        return count;
    }

    virtual std::streamsize xsputn(const char* s, std::streamsize n) override {
        // For reading only, xsputn is not implemented
        return 0;
    }

    virtual int sync() override {
        // For reading only, sync is not implemented
        return 0;
    }
};

class CustomFileStream : public std::istream {
public:
    CustomFileStream(const char* filename) : std::istream(&custom_buffer) {
        custom_buffer.open(filename);
    }

private:
    CustomBuffer custom_buffer;
};

// Function to measure time taken for reading a file
double measureTime(const char* filename) {
    auto start = std::chrono::high_resolution_clock::now();

    CustomFileStream stream(filename);
    string line;
    while (getline(stream, line)) {
        // Do nothing with the line for simplicity
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return static_cast<double>(duration.count()) / 1000.0; // Return in milliseconds
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    // Generate a random file with 10 MB of data
    const char* filename = "random_data.txt";
    ofstream outputFile(filename);
    const int dataSize = 10 * 1024 * 1024; // 10 MB
    for (int i = 0; i < dataSize; ++i) {
        outputFile << static_cast<char>(rand() % 256);
    }
    outputFile.close();

    cout << "Buffer Size: " << CustomBuffer::BUFFER_SIZE << " bytes" << endl;

    // Measure reading time with different buffer sizes
    cout << "Reading time with " << CustomBuffer::BUFFER_SIZE << " byte buffer: "
         << measureTime(filename) << " ms" << endl;

    // Change the buffer size and measure again (you need to recompile for this change to take effect)
    // ...

    return 0;
}
