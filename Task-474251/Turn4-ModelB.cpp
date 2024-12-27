#include <iostream>
#include <thread>
#include <future>
#include <algorithm>
#include <vector>
#include <chrono>
#include <atomic>
#include <queue>

const int N = 10000;

void calculateSquare(int x, int& result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result += x * x;
        }
    }
}

class WorkManager {
public:
    WorkManager(int num_threads) : thread_pool(num_threads) {
        for (int i = 0; i < num_threads; ++i) {
            thread_pool.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(work_mutex);
                        work_condition.wait(lock, [this] {
                            return work_queue.empty() || !shutdown;
                        });
                        if (shutdown && work_queue.empty()) {
                            return;
                        }
                        task = std::move(work_queue.front());
                        work_queue.pop();
                    }
                    task();
                }
            });
        }
    }

    void submit(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(work_mutex);
            work_queue.emplace_back(std::move(task));
        }
        work_condition.notify_one();
    }

    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(work_mutex);
            shutdown = true;
        }
        work_condition.notify_all();
    }

private:
    std::vector<std::thread> thread_pool;
    std::queue<std::function<void()>> work_queue;
    std::mutex work_mutex;
    std::condition_variable work_condition;
    bool shutdown = false;
};

int main() {
    int result_1 = 0, result_2 = 0;
    // Synchronous execution
    std::cout << "Synchronous execution:\n";
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        calculateSquare(1, result_1);
        calculateSquare(2, result_2);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
    }
    // Dynamic concurrency with WorkManager
    std::cout << "\nDynamic concurrency with WorkManager:\n";
    {
        WorkManager work_manager(std::thread::hardware_concurrency());

        auto start_time = std::chrono::high_resolution_clock::now();
        work_manager.submit([&] { calculateSquare(1, result_1); });
        work_manager.submit([&] { calculateSquare(2, result_2); });

        work_manager.shutdown();
        work_manager.thread_pool.join();

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
    }
    return 0;
}
