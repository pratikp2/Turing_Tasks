#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <condition_variable>

void workerThread(int priority, std::mutex& mtx, std::condition_variable& cond) {
    std::this_thread::sleep_for(std::chrono::seconds(priority)); // Simulate work

    {
        std::unique_lock<std::mutex> lock(mtx);
        cond.notify_all(); // Signal completion
    }

    std::cout << "Thread with priority " << priority << " completed." << std::endl;
}

int main() {
    std::mutex mtx;
    std::condition_variable cond;
    std::vector<std::thread> threads;

    // Create multiple threads with different priorities
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(workerThread, i, std::ref(mtx), std::ref(cond));
    }

    // Wait for all threads to complete using condition variables
    for (auto& thread : threads) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock);
        }
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << "All threads have completed." << std::endl;

    return 0;
}
