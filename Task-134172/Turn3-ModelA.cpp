```c++
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <functional>
#include <faker-cpp/Faker.hpp>

class DataMaskingPipeline {
public:
  using DataType = std::string;
  using MaskingFunction = std::function<void(DataType&)>;

  DataMaskingPipeline(size_t num_threads) : stop(false) {
    for (size_t i = 0; i < num_threads; ++i) {
      workers.emplace_back([this] { workerThread(); });
    }
  }

  ~DataMaskingPipeline() {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
      worker.join();
    }
  }

  template <typename... Args>
  void addMaskingFunction(Args&&... args) {
    maskingFunctions.emplace_back(std::forward<Args>(args)...);
  }

  void pushData(const DataType& data) {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      dataQueue.push(data);
    }
    condition.notify_one();
  }

private:
  void workerThread() {
    DataType data;
    while (true) {
      {
        std::unique_lock<std::mutex> lock(queue_mutex);
        condition.wait(lock, [this] { return stop || !dataQueue.empty(); });
        if (stop && dataQueue.empty()) {
          return;
        }
        data = std::move(dataQueue.front());
        dataQueue.pop();
      }

      for (const MaskingFunction& maskingFunc : maskingFunctions) {
        maskingFunc(data);
      }
    }
  }

  std::vector<std::thread> workers;
  std::vector<MaskingFunction> maskingFunctions;
  std::queue<DataType> dataQueue;
  std::mutex queue_mutex;
  std::condition_variable condition;
  std::atomic<bool> stop;
};

int main() {
  const size_t num_threads = std::thread::hardware_concurrency();
  DataMaskingPipeline pipeline(num_threads);

  // Define your masking functions
  auto maskPersonalInfo = [](std::string& data) {
    // Mask personal information using regular expressions or Faker-cpp
    Faker faker;
    data = faker.name().name();
  };

  auto maskPhoneNumber = [](std::string& data) {
    // Mask phone numbers using regular expressions
    // ...
  };

  // Add masking functions to the pipeline
  pipeline.addMaskingFunction(maskPersonalInfo);
  pipeline.addMaskingFunction(maskPhoneNumber);

  // Generate and push data into the pipeline for real-time processing
  for (int i = 0; i < 100; ++i) {
    std::string data = "John Doe, (123) 456-7890"; // Replace this with real data
    pipeline.pushData(data);
  }

  // Wait for the pipeline to process all the data
  // ...

  return 0;
}
 ```