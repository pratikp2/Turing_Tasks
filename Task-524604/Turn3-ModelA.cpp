#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <ctime>

// Struct to keep track of string buffers
struct StringBuffer {
    char *buffer;
    size_t size;

    StringBuffer(size_t size) : size(size) {
        buffer = new char[size];
        buffer[0] = '\0'; // Initialize to empty string
    }

    ~StringBuffer() {
        delete[] buffer;
    }
};

// Debugging Logging Utility
class DebugLogger {
public:
    static void Log(const std::string &message) {
        std::cout << "[" << GetTimestamp() << "] " << message << std::endl;
    }

private:
    static std::string GetTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return buf;
    }
};

// Global memory tracker
class MemoryTracker {
public:
    static void TrackMemoryUsage(size_t allocated, size_t freed) {
        currentUsage += allocated;
        currentUsage -= freed;
        LogMemoryUsage();
    }

    static void LogMemoryUsage() {
        DebugLogger::Log("Current Memory Usage: " + std::to_string(currentUsage) + " bytes");
    }

private:
    static size_t currentUsage;
};

size_t MemoryTracker::currentUsage = 0;

// Safe string copy function
void SafeStrCpy(char *dest, size_t dest_size, const char *src) {
    size_t src_len = std::strlen(src);
    if (src_len >= dest_size) {
        DebugLogger::Log("Warning: Attempt to copy string exceeds buffer size.");
        throw std::overflow_error("Buffer overflow in SafeStrCpy");
    }
    std::strcpy(dest, src);
    MemoryTracker::TrackMemoryUsage(src_len + 1, 0); // +1 for null terminator
    DebugLogger::Log("SafeStrCpy executed");
}

// Safe string length function
size_t SafeStrLen(const char *str) {
    size_t len = std::strlen(str);
    DebugLogger::Log("SafeStrLen executed");
    return len;
}

int main() {
    try {
        const size_t BUFFER_SIZE = 50; // Limit for our buffers
        StringBuffer buf1(BUFFER_SIZE);
        
        // Test data
        const char *testStr = "This is a test string that is intentionally long to test buffer overflow.";
        
        // Example 1: Performing safe string copy
        SafeStrCpy(buf1.buffer, BUFFER_SIZE, "Short String");
        std::cout << "Buffer 1: " << buf1.buffer << std::endl;

        // Example 2: Attempting to copy a long string to demonstrate tracking
        try {
            SafeStrCpy(buf1.buffer, BUFFER_SIZE, testStr);
        } catch (const std::overflow_error &e) {
            DebugLogger::Log(std::string("Exception: ") + e.what());
        }

        // Get the length of a string
        size_t length = SafeStrLen(buf1.buffer);
        std::cout << "Length of Buffer 1: " << length << std::endl;

    } catch (const std::exception &e) {
        DebugLogger::Log(std::string("General Exception: ") + e.what());
    }

    return 0;
}
