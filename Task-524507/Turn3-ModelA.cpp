#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

const int SIZE = 100;
int sharedArray[SIZE]; // Shared array
const int iterations = 1000;

// Thread function to update the shared array
void updateArray(int threadId) {
    for (int i = 0; i < iterations; ++i) {
        sharedArray[threadId]++; // Increment the element corresponding to the thread ID
        
        // Introducing a memory barrier after the write operation
        std::atomic_thread_fence(std::memory_order_seq_cst);
    }
}

// Thread function to read and print the shared array values
void readArray() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Ensuring that updates have occurred

    for (int i = 0; i < SIZE; ++i) {
        // Introducing a memory barrier before reading
        std::atomic_thread_fence(std::memory_order_seq_cst);
        std::cout << "Value at index " << i << ": " << sharedArray[i] << std::endl;
    }
}

int main() {
    // Initialize the shared array
    for (int i = 0; i < SIZE; ++i) {
        sharedArray[i] = 0;
    }

    // Create threads to update the shared array
    std::thread threads[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        threads[i] = std::thread(updateArray, i);
    }

    // Create a thread to read the shared array
    std::thread reader(readArray);

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
