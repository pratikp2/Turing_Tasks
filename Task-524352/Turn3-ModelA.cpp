#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

// Define the number of threads and the number of increments each thread should perform
const int numThreads = 10;
const int incrementsPerThread = 1000;

// Shared atomic counter
std::atomic<int> sharedCounter(0);

// Function that each thread will execute
void incrementCounter() {
    for (int i = 0; i < incrementsPerThread; ++i) {
        // Atomically increment the shared counter
        sharedCounter.fetch_add(1, std::memory_order_relaxed);
        
        // Optional: simulate some work
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

int main() {
    // Create a vector to hold the threads
    std::vector<std::thread> threads;

    // Start multiple threads that will increment the counter
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Output the final value of the shared counter
    std::cout << "Final Counter Value: " << sharedCounter.load() << std::endl;

    return 0;
}
