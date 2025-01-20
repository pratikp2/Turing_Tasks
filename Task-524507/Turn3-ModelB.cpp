#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

// Shared array
int sharedArray[1000] = {0};

// Number of threads
const int numThreads = 4;
// Number of iterations per thread
const int iterations = 10000;

// Function to update the array elements by thread
void updateArrayElements(int threadId, int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; ++i) {
        sharedArray[i] += threadId; // Race condition exists here without barrier
    }
    
    // At the end of thread execution, ensure all writes to sharedArray are visible
    std::atomic_thread_fence(std::memory_order_release);
}

int main() {
    const int elementsPerThread = iterations / numThreads + 1;

    std::thread threads[numThreads];

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        int startIndex = threadId * elementsPerThread;
        int endIndex = min((threadId + 1) * elementsPerThread, iterations) - 1;
        threads[threadId] = std::thread(updateArrayElements, threadId, startIndex, endIndex);
    }

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        threads[threadId].join();
    }
    // Inserting a memory fence after all threads have joined
    // Ensures we see the last updated values
    std::atomic_thread_fence(std::memory_order_acquire);

    // Print the updated shared array
    for (int i = 0; i < iterations; ++i) {
        std::cout << sharedArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
