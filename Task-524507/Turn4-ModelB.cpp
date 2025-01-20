#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <chrono>

const int SIZE = 1000;
int sharedArray[SIZE]; // Shared array
std::mutex syncMutex;  // Mutex for synchronized access
int notifyIndex = -1; // Atomic int for notifying array access
std::atomic<bool> notifyReady(false); // Atomic flag to sync threads
const int iterations = 10000;

// Thread function to increment elements concurrently
void incrementElementsConcurrently(int threadId) {
    for (int i = 0; i < iterations; ++i) {
        int index = threadId * (iterations / 4) + (i % (iterations / 4));
        sharedArray[index]++; // Increment element concurrently without strict ordering need
    }

    // Flag the end of concurrent increments and acquire mutex for notification
    notifyIndex = threadId;
    notifyReady.store(true);
    syncMutex.lock();
}

// Thread function to update an element that requires strict synchronization
void updateElementStrictly() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    while (!notifyReady.load()) {
        std::this_thread::yield(); // Yield till notification is ready
    }
    
    int syncIndex = notifyIndex; // This thread uses mutex to write exclusively
    
    // Fine-grained critical section: only this thread should see the latest iterations
    {
        std::lock_guard<std::mutex> guard(syncMutex);
        for (int i = 0; i < iterations; ++i) {
            int incrementIndex = syncIndex * (iterations / 4) + (i % (iterations / 4));
            sharedArray[incrementIndex] *= 2; // Strict sync for updating array values 
        }
    }
    
    notifyReady.store(false);
}

// Thread function to print the shared array values
void printArray() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    {
        std::lock_guard<std::mutex> guard(syncMutex);
        std::cout << "Final values in shared array:" << std::endl;
        for (int i = 0; i < SIZE; ++i) {
            std::cout << "Value at index " << i << ": " << sharedArray[i] << std::endl;
        }
    }
}

int main() {
    // Initialize the shared array
    for (int i = 0; i < SIZE; ++i) {
        sharedArray[i] = 0;
    }
    
    // Create threads to increment elements concurrently
    std::thread threads[4];
    for (int i = 0; i < 4; ++i) {
        threads[i] = std::thread(incrementElementsConcurrently, i);
    }
    
    // Create a thread to update the array strictly using mutex
    std::thread strictUpdateThread(updateElementStrictly);
    
    // Create a thread to read the shared array
    std::thread printer(printArray);
    
    // Join threads
    for (int i = 0; i < 4; ++i) {
        threads[i].join();
    }
    strictUpdateThread.join();
    printer.join();

    return 0;
}
