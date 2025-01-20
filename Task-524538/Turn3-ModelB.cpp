#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>

// Inline function for atomic increment
inline void atomicIncrement(std::atomic<int>& counter) {
    counter.fetch_add(1, std::memory_order_relaxed);
}

// Function to increment the shared counter multiple times
void incrementCounter(std::atomic<int>& sharedCounter, int numIncrements) {
    for (int i = 0; i < numIncrements; ++i) {
        atomicIncrement(sharedCounter);
    }
}

int main() {
    const int numThreads = 10;
    const int iterationsPerThread = 1000000;
    std::atomic<int> sharedCounter(0);

    std::vector<std::thread> threads;

    // Create and start threads to increment the counter concurrently
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter, std::ref(sharedCounter), iterationsPerThread);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final value of the shared counter
    std::cout << "Final shared counter value: " << sharedCounter.load(std::memory_order_acquire) << std::endl;

    return 0;
}
