#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstddef>
#include <ctime>

#define VALGRIND_MALLOC(size) malloc(size)
#define VALGRIND_FREE(ptr) free(ptr)

// Struct to keep track of string buffers
struct StringBuffer {
    char *buffer;
    size_t size;

    StringBuffer(size_t size) : size(size) {
        buffer = (char *)VALGRIND_MALLOC(size);
        memset(buffer, 0, size); // Initialize buffer to nulls
    }

    ~StringBuffer() {
        VALGRIND_FREE(buffer);
    }
};

// Debugging Logging Utility
class DebugLogger {
public:
    static void Log(const std::string &message, const char *file = __FILE__, size_t line = __LINE__) {
        std::cout << "[" << GetTimestamp() << "] [" << file << ":" << line << "] " << message << std::endl;
    }

private:
    static std::string GetTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return buf;
    }
};

// Safe string copy function
void SafeStrCpy(char *dest, size_t dest_size, const char *src) {
    size_t src_len = std::strlen(src);
    if (src_len >= dest_size) {
        DebugLogger::Log("Warning: Attempt to copy string exceeds buffer size. Source string length: " + std::to_string(src_len) + ", Destination buffer size: " + std::to_string(dest_size), __FILE__, __LINE__);
        throw std::overflow_error("Buffer overflow in SafeStrCpy");
    }
    std::strcpy(dest, src);
    DebugLogger::Log("SafeStrCpy executed", __FILE__, __LINE__);
}

// Safe string length function
size_t SafeStrLen(const char *str) {
    size_t len = std::strlen(str);
    DebugLogger::Log("SafeStrLen executed", __FILE__, __LINE__);
    return len;
}

int main() {
    try {
        const size_t BUFFER_SIZE = 20;
        StringBuffer buf1(BUFFER_SIZE);

        const char *testStr = "This is a test string for buffer overflow";

        SafeStrCpy(buf1.buffer, BUFFER_SIZE, testStr);
        std::cout << "Buffer 1: " << buf1.buffer << std::endl;

    } catch (const std::exception &e) {
        DebugLogger::Log(std::string("General Exception: ") + e.what(), __FILE__, __LINE__);
    }

    return 0;
}
