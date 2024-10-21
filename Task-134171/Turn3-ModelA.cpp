#include <thread>
#include <vector>
#include <queue>
#include <atomic>

std::vector<std::thread> workers;
std::queue<std::function<void()>> taskQueue;
std::atomic<bool> stopFlag{false};

void workerThread() {
  while (!stopFlag.load()) {
    if (!taskQueue.empty()) {
      auto task = std::move(taskQueue.front());
      taskQueue.pop();
      task();
    }
    std::this_thread::yield();
  }
}

void startThreadPool(size_t numThreads) {
  workers.reserve(numThreads);
  for (size_t i = 0; i < numThreads; ++i) {
    workers.emplace_back(workerThread);
  }
}

void enqueueTask(std::function<void()> task) {
  taskQueue.push(std::move(task));
}

void stopThreadPool() {
  stopFlag.store(true);
  for (std::thread& worker : workers) {
    worker.join();
  }
}
   // Usage:
  startThreadPool(std::thread::hardware_concurrency());

  // Enqueue tasks dynamically based on the workload
  enqueueTask([]() { workOnTask1(); });
  enqueueTask([]() { workOnTask2(); });
  // ...

  stopThreadPool();