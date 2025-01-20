#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <chrono>

const int SIZE = 100;
int sharedArray[SIZE];
std::mutex mutex; // Mutex for synchronization
const int iterations = 1000;

// A function to safely increment the shared array using a mutex
void incrementSharedArray(int threadId) {
    for (int i = 0; i < iterations; ++i) {
        {
            std::lock_guard<std::mutex> lock(mutex); // Lock the mutex for exclusive access
            sharedArray[threadId]++; // Increment the element corresponding to the thread ID
            // Memory barrier to ensure visibility after modification
            std::atomic_thread_fence(std::memory_order_seq_cst);
        }
    }
}

// A function to read the shared array with memory barriers
void readSharedArray() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Ensure all threads have had time to increment
    for (int i = 0; i < SIZE; ++i) {
        // Memory barrier before reading
        std::atomic_thread_fence(std::memory_order_seq_cst);
        std::cout << "Value at index " << i << ": " << sharedArray[i] << std::endl;
    }
}

int main() {
    // Initialize the shared array with zeros
    for (int i = 0; i < SIZE; ++i) {
        sharedArray[i] = 0;
    }

    // Create threads to increment the shared array
    std::thread threads[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        threads[i] = std::thread(incrementSharedArray, i);
    }

    // Create a thread to read the shared array
    std::thread reader(readSharedArray);

    // Join threads
    for (int i = 0; i < SIZE; ++i) {
        threads[i].join();
    }
    reader.join();

    std::cout << "Final values in shared array:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << "Value at index " << i << ": " << sharedArray[i] << std::endl;
    }

    return 0;
}
