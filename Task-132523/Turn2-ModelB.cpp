#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>

class IoTDataManager {
public:
  using DataPoint = std::vector<float>;
  using DataContainer = std::vector<DataPoint>;

private:
  std::vector<DataContainer> partitions_;
  size_t max_partition_size_;
  std::queue<DataPoint> data_queue_;
  std::thread partition_thread_;
  std::mutex mutex_;
  bool stop_thread_ = false;

public:
  IoTDataManager(size_t num_partitions, size_t max_partition_size) : max_partition_size_(max_partition_size) {
    partitions_.resize(num_partitions);
    partition_thread_ = std::thread(&IoTDataManager::automatePartitionMaintenance, this);
  }

  ~IoTDataManager() {
    stop_thread_ = true;
    partition_thread_.join();
  }

  void addDataPoint(const DataPoint& data) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      data_queue_.push(data);
    }
  }

  // Automate real-time partition maintenance
  void automatePartitionMaintenance() {
    while (!stop_thread_) {
      std::lock_guard<std::mutex> lock(mutex_);
      if (data_queue_.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        continue;
      }

      DataPoint data = data_queue_.front();
      data_queue_.pop();

      // Assuming the first element represents the timestamp
      size_t partition_index = static_cast<size_t>(data[0] / (1.0f / partitions_.size()));

      if (partitions_[partition_index].size() >= max_partition_size_) {
        // Partition is full, remove the oldest data point
        partitions_[partition_index].erase(partitions_[partition_index].begin());
      }

      partitions_[partition_index].push_back(data);
    }
  }

  size_t getNumDataPoints() const {
    size_t total_data_points = 0;
    for (const auto& partition : partitions_) {
      total_data_points += partition.size();
    }
    return total_data_points;
  }