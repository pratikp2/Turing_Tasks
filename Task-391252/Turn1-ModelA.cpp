#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void workerThread(int priority) {
    std::this_thread::sleep_for(std::chrono::seconds(priority)); // Simulate work with a delay
    std::cout << "Thread with priority " << priority << " completed." << std::endl;
}

int main() {
    std::vector<std::thread> threads;

    // Create multiple threads with different priorities
    for (int i = 1; i <= 3; ++i) {
        // Use std::thread::native_handle to set priority (platform-specific)
        // For this example, we'll simulate priority by sleep time
        threads.emplace_back(workerThread, i);
    }

    // Check and manage threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            std::cout << "Thread is joinable. Joining..." << std::endl;
            thread.join(); // Wait for the thread to complete
        } else {
            std::cout << "Thread is not joinable." << std::endl;
        }
    }

    std::cout << "All threads have completed." << std::endl;

    return 0;
}
