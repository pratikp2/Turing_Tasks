#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(int numThreads) : numThreads_(numThreads) {
        for (int i = 0; i < numThreads_; ++i) {
            workers_.push_back(std::thread(&ThreadPool::workerThread, this));
        }
    }

    ~ThreadPool() {
        shutdown_.store(true);
        taskQueue_.notify_all();
        for (std::thread& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void addTask(const std::function<void()>& task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            taskQueue_.push(task);
        }
        taskQueue_.notify_one();
    }

private:
    void workerThread() {
        while (!shutdown_.load()) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex_);
                taskQueue_.wait(lock, [this] { return !taskQueue_.empty() || shutdown_.load(); });
                if (shutdown_.load()) {
                    return;
                }
                task = std::move(taskQueue_.front());
                taskQueue_.pop();
            }
            task();
        }
    }

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> taskQueue_;
    std::mutex queueMutex_;
    std::condition_variable condition_;
    std::atomic<bool> shutdown_;
    int numThreads_;
};

void processTransaction(int transactionId) {
    std::cout << "Processing transaction " << transactionId << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
}

int main() {
    ThreadPool pool(4);  // Create a thread pool with 4 worker threads

    for (int i = 0; i < 10; ++i) {
        pool.addTask([i]() { processTransaction(i); });
    }

    // Wait for all tasks to complete
    pool.addTask([&pool]() {
        pool.joinAll();
    });

    return 0;
}