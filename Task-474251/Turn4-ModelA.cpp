#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <chrono>
#include <atomic>

const int N = 10000;
std::atomic<int> active_tasks(0);

// Simulated workload function
void calculateSquare(int x) {
    active_tasks++;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            volatile int temp = x * x;  // To simulate work
        }
    }
    active_tasks--;
}

int main() {
    const int max_concurrent_tasks = std::thread::hardware_concurrency();
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 200; ++i) {  // Simulated 200 workloads
        while (active_tasks >= max_concurrent_tasks) {
            // Wait until the number of active tasks falls below the threshold
            std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Polling interval
        }
        // Launch an async task for this workload
        futures.push_back(std::async(std::launch::async, calculateSquare, i));
    }

    // Wait for all futures to complete
    for (auto& fut : futures) {
        fut.get();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
