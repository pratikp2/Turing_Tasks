#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

// Shared counter
int sharedCounter = 0;

// Number of iterations for each thread
const int iterations = 100000;

// Function to increment the shared counter without proper synchronization
void incrementCounterUnsafe() {
    for (int i = 0; i < iterations; ++i) {
        sharedCounter++;  // Unsafe increment; no memory barriers or atomic operations
    }
}

// Function to check and report the final value of the counter
void checkCounter() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for threads to finish
    std::cout << "Final shared counter: " << sharedCounter << std::endl;
}

int main() {
    std::cout << "Starting unsafe increment..." << std::endl;
    
    std::thread t1(incrementCounterUnsafe);
    std::thread t2(incrementCounterUnsafe);
    
    // Start a thread to check the counter afterward
    std::thread checker(checkCounter);

    // Join threads
    t1.join();
    t2.join();
    checker.join();

    return 0;
}
