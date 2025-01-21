#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <map>
#include <iomanip>
#include <thread>

// Custom memory manager to track allocations
class CustomMemoryManager {
private:
    static std::map<void*, size_t> allocatedMemory;

public:
    static void* allocate(size_t size) {
        void* ptr = ::operator new(size);
        allocatedMemory[ptr] = size;
        DebugLogger::Log("Memory allocated: " + std::to_string(size) + " bytes at " + std::to_string((uintptr_t)ptr));
        return ptr;
    }

    static void deallocate(void* ptr) {
        if (allocatedMemory.find(ptr) == allocatedMemory.end()) {
            DebugLogger::Log("Memory deallocation error: Pointer not found.");
        } else {
            size_t size = allocatedMemory[ptr];
            ::operator delete(ptr);
            allocatedMemory.erase(ptr);
            DebugLogger::Log("Memory deallocated: " + std::to_string(size) + " bytes at " + std::to_string((uintptr_t)ptr));
        }
    }

    static std::map<void*, size_t>& getAllocatedMemory() {
        return allocatedMemory;
    }
};

// Struct to keep track of string buffers
struct StringBuffer {
    char *buffer;
    size_t size;

    StringBuffer(size_t size) : size(size) {
        buffer = (char*)CustomMemoryManager::allocate(size);
        buffer[0] = '\0'; // Initialize to empty string
    }

    ~StringBuffer() {
        CustomMemoryManager::deallocate(buffer);
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

// Safe string copy function
void SafeStrCpy(char *dest, size_t dest_size, const char *src) {
    size_t dest_available = dest_size - 1; // Account for the null terminator
    size_t src_length = SafeStrLen(src);

    if (src_length >= dest_available) {
        DebugLogger::Log("Buffer overflow in SafeStrCpy: Destination size = " + std::to_string(dest_available) + ", Source length = " + std::to_string(src_length));
        throw std::overflow_error("Buffer overflow in SafeStrCpy");
    }
    std::strcpy(dest, src);
    DebugLogger::Log("SafeStrCpy executed successfully");
}

// Safe string length function
size_t SafeStrLen(const char *str) {
    return std::strlen(str);
}

// Function to simulate a real-time scenario with multiple threads
void RealTimeScenario() {
    try {
        StringBuffer buf1(20);
        StringBuffer buf2(10);

        const char *testStrLong = "This is a long string to test buffer overflow.";
        const char *testStrShort = "Short string";

        // Thread 1: Performing safe operations
        std::thread thread1([&] {
            SafeStrCpy(buf1.buffer, buf1.size, testStrShort);
            DebugLogger::Log("Thread 1: Buffer 1 content: " + std::string(buf1.buffer));

            std::this_thread::sleep_for(std::chrono::seconds(1));
        });

        // Thread 2: Attempting unsafe operation
        std::thread thread2([&] {
            SafeStrCpy(buf2.buffer, buf2.size, testStrLong);
            DebugLogger::Log("Thread 2: Buffer 2 content: " + std::string(buf2.buffer));
        });

        thread1.join();
        thread2.join();

    } catch (const std::overflow_error &e) {
        DebugLogger::Log(std::string("Exception: ") + e.what());
    } catch (const std::exception &e) {
        DebugLogger::Log(std::string("General Exception: ") + e.what());
    }
}

int main() {
    DebugLogger::Log("Starting memory monitoring...");

    try {
        RealTimeScenario();

        DebugLogger::Log("Memory usage report:");
        for (const auto& entry : CustomMemoryManager::getAllocatedMemory()) {
            DebugLogger::Log("Address: " + std::to_string((uintptr_t)entry.first) + ", Size: " + std::to_string(entry.second));
        }

    } catch (const std::exception &e) {
        DebugLogger::Log(std::string("Exception in main: ") + e.what());
    }

    DebugLogger::Log("Memory monitoring completed.");
    return 0;
}
