#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::mutex mtx;

enum Command {
    CMD_INCREMENT,
    CMD_DECREMENT,
    CMD_PRINT,
    CMD_EXIT,
    CMD_UNKNOWN
};

class SharedResource {
public:
    int value;

    SharedResource() : value(0) {}

    void processCommand(Command cmd) {
        std::lock_guard<std::mutex> lock(mtx); // Lock for the duration of command processing

        switch (cmd) {
            case CMD_INCREMENT:
                ++value;
                std::cout << "Incremented: " << value << std::endl;
                break;
            case CMD_DECREMENT:
                --value;
                std::cout << "Decremented: " << value << std::endl;
                break;
            case CMD_PRINT:
                std::cout << "Current value: " << value << std::endl;
                break;
            case CMD_EXIT:
                std::cout << "Exiting thread" << std::endl;
                break;
            default:
                std::cout << "Unknown command" << std::endl;
        }
    }
};

void threadFunction(SharedResource &resource, Command cmd) {
    resource.processCommand(cmd);
    // Simulate some delay
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main() {
    SharedResource resource;
    std::vector<std::thread> threads;

    // Create threads with different commands
    threads.push_back(std::thread(threadFunction, std::ref(resource), CMD_INCREMENT));
    threads.push_back(std::thread(threadFunction, std::ref(resource), CMD_PRINT));
    threads.push_back(std::thread(threadFunction, std::ref(resource), CMD_DECREMENT));
    threads.push_back(std::thread(threadFunction, std::ref(resource), CMD_PRINT));
    threads.push_back(std::thread(threadFunction, std::ref(resource), CMD_EXIT));

    // Join all threads
    for (auto &t : threads) {
        t.join();
    }

    return 0;
}
