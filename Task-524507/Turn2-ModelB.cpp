#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Shared counter (without atomicity initially)
int sharedCounter = 0;

// Function to increment the shared counter without memory barriers
void incrementCounterWithoutBarrier(int numIncrements) {
    for (int i = 0; i < numIncrements; ++i) {
        sharedCounter++;
    }
}

// Function to increment the shared counter with memory barriers
void incrementCounterWithBarrier(int numIncrements) {
    for (int i = 0; i < numIncrements; ++i) {
        sharedCounter++;
        // Use a memory barrier to ensure writes are visible
        std::atomic_thread_fence(std::memory_order_seq_cst);
    }
}

// Main function
int main() {
    const int numThreads = 4;
    const int numIncrementsPerThread = 1000000;

    // Without memory barriers
    std::cout << "\nTest without memory barriers:\n";
    sharedCounter = 0;

    std::thread threadsWithoutBarrier[numThreads];

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        threadsWithoutBarrier[threadId] = std::thread(incrementCounterWithoutBarrier, numIncrementsPerThread);
    }

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        threadsWithoutBarrier[threadId].join();
    }

    std::cout << "Final counter value without memory barriers: " << sharedCounter << std::endl;
    // Expected value: 4 * 1000000 = 4000000, but may be incorrect due to lack of barriers

    // With memory barriers
    std::cout << "\nTest with memory barriers:\n";
    sharedCounter = 0;

    std::thread threadsWithBarrier[numThreads];

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        threadsWithBarrier[threadId] = std::thread(incrementCounterWithBarrier, numIncrementsPerThread);
    }

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        threadsWithBarrier[threadId].join();
    }

    std::cout << "Final counter value with memory barriers: " << sharedCounter << std::endl;
    // Expected value: 4 * 1000000 = 4000000, and should be correct with barriers

    return 0;
}
