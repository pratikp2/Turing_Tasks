#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
#include <condition_variable>

#define THREAD_COUNT 3

void workerThread(int priority, std::mutex& mtx, std::condition_variable& cond, std::atomic<bool>& shouldContinue) {
    while (shouldContinue.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(priority)); // Simulate work
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.notify_all(); // Signal completion
        }
        std::cout << "Thread with priority " << priority << " completed an iteration." << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cond;
    std::atomic<bool> shouldContinue(true);

    // Create threads with different simulated priorities
    for (int i = 1; i <= THREAD_COUNT; ++i) {
        threads.emplace_back(workerThread, i, std::ref(mtx), std::ref(cond), std::ref(shouldContinue));
    }

    // Simulate work in the main thread
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait for a while

    // Signal threads to stop
    shouldContinue.store(false);
    {
        std::unique_lock<std::mutex> lock(mtx);
        cond.notify_all(); // Wake up any sleeping threads
    }

    // Join all threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            std::cout << "Thread is joinable. Joining..." << std::endl;
            thread.join();
        } else {
            std::cout << "Thread is not joinable." << std::endl;
        }
    }

    std::cout << "All threads have completed." << std::endl;

    return 0;
}
