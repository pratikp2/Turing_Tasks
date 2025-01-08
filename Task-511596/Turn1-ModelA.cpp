#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

// Enum to define various I/O operation types
enum class IOOperation {
    READ,
    WRITE,
    CLOSE,
    TIMEOUT
};

// Simulated I/O handler
class IOHandler {
public:
    void executeOperation(IOOperation op) {
        try {
            std::unique_lock<std::mutex> lock(mMutex);
            switch (op) {
                case IOOperation::READ:
                    performRead();
                    break;
                case IOOperation::WRITE:
                    performWrite();
                    break;
                case IOOperation::CLOSE:
                    performClose();
                    break;
                case IOOperation::TIMEOUT:
                    handleTimeout();
                    break;
                default:
                    throw std::invalid_argument("Unknown operation");
            }
        } catch (const std::exception &e) {
            logException(e);
        }
    }

private:
    std::mutex mMutex;

    void performRead() {
        // Simulating a read operation
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Read operation completed." << std::endl;
    }

    void performWrite() {
        // Simulating a write operation
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Write operation completed." << std::endl;
    }

    void performClose() {
        // Simulating a close operation
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Close operation completed." << std::endl;
    }

    void handleTimeout() {
        // Handle timeout scenario
        std::cout << "Handling timeout." << std::endl;
    }

    void logException(const std::exception &e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
};

int main() {
    IOHandler ioHandler;
    std::atomic<bool> keepRunning{true};

    // Example of multiple I/O operations in multiple threads
    std::thread reader([&]() {
        while (keepRunning) {
            ioHandler.executeOperation(IOOperation::READ);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread writer([&]() {
        while (keepRunning) {
            ioHandler.executeOperation(IOOperation::WRITE);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // Allow for the threads to run for a short time
    std::this_thread::sleep_for(std::chrono::seconds(1));
    keepRunning = false; // Stop the threads

    reader.join();
    writer.join();

    return 0;
}
