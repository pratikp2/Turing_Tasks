#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<int> sharedCounter(0);

// Function to increment the shared counter concurrently
void incrementCounter() {
    for (int i = 0; i < 100000; ++i) {
        // Increment the shared counter atomically
        sharedCounter.fetch_add(1, std::memory_order_release);
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    // Start multiple threads to increment the counter concurrently
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter);
    }

    // Wait for all threads to finish their work
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final value of the shared counter
    std::cout << "Final value of the shared counter: " << sharedCounter.load() << std::endl;

    return 0;
}
