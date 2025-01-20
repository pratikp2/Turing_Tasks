#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> safeSharedCounter(0);
const int iterations = 100000;

void incrementCounterSafe() {
    for (int i = 0; i < iterations; ++i) {
        safeSharedCounter.fetch_add(1);  // This is atomic
    }
}

void checkCounter() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for threads to finish
    std::cout << "Final safe shared counter: " << safeSharedCounter.load() << std::endl;
}

int main() {
    std::cout << "Starting safe increment..." << std::endl;

    std::thread t1(incrementCounterSafe);
    std::thread t2(incrementCounterSafe);
    
    // Start a thread to check the counter afterward
    std::thread checker(checkCounter);

    // Join threads
    t1.join();
    t2.join();
    checker.join();

    return 0;
}