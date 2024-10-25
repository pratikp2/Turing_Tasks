
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <queue>
#include <functional>

// Class to represent a task that needs to be executed lazily
class LazyTask {
public:
  using Task = std::function<void()>;

  LazyTask(Task task) : task(std::move(task)), isEvaluated(false) {}

  void evaluate() {
    if (!isEvaluated) {
      task();
      isEvaluated = true;
    }
  }

private:
  Task task;
  std::atomic_bool isEvaluated;
};

// Class to manage lazy tasks and execute them efficiently
class LazyTaskManager {
public:
  void addTask(LazyTask::Task task) {
    tasks.push(std::make_shared<LazyTask>(std::move(task)));
    condition.notify_one();
  }

  void startWorkerThreads(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
      workers.emplace_back([this] {
        while (true) {
          std::shared_ptr<LazyTask> task;

          {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) {
              return;
            }
            task = std::move(tasks.front());
            tasks.pop();
          }

          task->evaluate();
        }
      });
    }
  }

  void stop() {
    {
      std::unique_lock<std::mutex> lock(mutex);
      stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
      worker.join();
    }
  }

private:
  std::queue<std::shared_ptr<LazyTask>> tasks;
  std::vector<std::thread> workers;
  std::mutex mutex;
  std::condition_variable condition;
  bool stop = false;
};

// Simulate some work that needs to be done lazily on edge nodes
void simulateEdgeNodeWork(int nodeId) {
  std::cout << "Edge node " << nodeId << ": Performing lazy work..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(std::rand() % 3 + 1));
}

int main() {
  const size_t numEdgeNodes = 5;
  const size_t numWorkerThreads = 3;

  LazyTaskManager taskManager;

  // Add lazy tasks for each edge node
  for (int i = 0; i < numEdgeNodes; ++i) {
    taskManager.addTask([i] { simulateEdgeNodeWork(i); });
  }

  taskManager.startWorkerThreads(numWorkerThreads);

  // Main thread can do other tasks here while lazy tasks are executed in the background
  std::cout << "Main thread: Doing other work..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));

  taskManager.stop();

  std::cout << "Main thread: Exiting..." << std::endl;
  return 0;
}
