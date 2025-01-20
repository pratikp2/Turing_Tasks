#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

// Shared data array
double* sharedArray = new double[1000];

// Initialize the array
void initializeArray() {
    for (int i = 0; i < 1000; ++i) {
        sharedArray[i] = 0.0;
    }
}

// Thread function to update the array elements
void updateArrayElements(int threadId, int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; ++i) {
        sharedArray[i] = static_cast<double>(threadId) + 1.0;
    }
}

// Main function
int main() {
    initializeArray();

    const int numThreads = 4;
    const int elementsPerThread = 1000 / numThreads;

    std::thread threads[numThreads];

    // Start threads to update the array
    for (int threadId = 0; threadId < numThreads; ++threadId) {
        int startIndex = threadId * elementsPerThread;
        int endIndex = (threadId + 1) * elementsPerThread - 1;
        threads[threadId] = std::thread(updateArrayElements, threadId, startIndex, endIndex);
    }

    // Wait for all threads to complete
    for (int threadId = 0; threadId < numThreads; ++threadId) {
        threads[threadId].join();
    }

    // Use a memory barrier to ensure all writes are visible
    std::atomic_thread_fence(std::memory_order_seq_cst);

    // Print the updated array elements
    for (int i = 0; i < 1000; ++i) {
        std::cout << sharedArray[i] << " ";
    }
    std::cout << std::endl;

    // Free the dynamically allocated memory
    delete[] sharedArray;

    return 0;
}
