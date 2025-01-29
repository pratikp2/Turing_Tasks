#include <iostream>
#include <future>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <stdexcept>


template <typename Task>
class ThreadTask {
public:
    explicit ThreadTask(Task&& task) : task(std::move(task)) {}

    void operator()() {
        try {
            task();
        } catch (...) {
            std::cerr << "ThreadTask: An exception occurred in the task:\n";
        }
    }

private:
    Task task;
};

class ThreadPool {
public:
    ThreadPool(size_t num_threads) : threads(), task_queue() {
        for (size_t i = 0; i < num_threads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        condition.wait(lock, [this] { return !task_queue.empty() || stop; });
                        if (stop && task_queue.empty()) {
                            return;
                        }
                        task = std::move(task_queue.front());
                        task_queue.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    template <typename Task>
    auto enqueue(Task&& task) {
        std::packaged_task<void()> ptask(std::forward<Task>(task));
        std::future<void> task_future = ptask.get_future();
        {
            std::unique_lock<std::mutex> lock(mutex);
            task_queue.emplace(std::move(ptask));
        }
        condition.notify_one();
        return task_future;
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> task_queue;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop = false;
};

int main() {
    // Create a thread pool with 4 worker threads
    ThreadPool threadPool(4);
    const int numTasks = 10;

    // Enqueue some tasks
    for (int i = 0; i < numTasks; ++i) {
        threadPool.enqueue([i] {
            std::cout << "Task " << i << " started\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Task " << i << " finished\n";
        });
    }

    std::cout << "Main thread: Waiting for tasks to complete\n";

    // Block the main thread until all tasks are complete
    // Note: In practice, you'd want to handle ongoing tasks gracefully.
    
    return 0;
}
