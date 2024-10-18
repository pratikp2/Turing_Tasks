#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class IoTDataManager {
public:
  using DataPoint = std::vector<float>;
  using DataContainer = std::vector<DataPoint>;

private:
  DataContainer data_;
  size_t max_partition_size_;

public:
  IoTDataManager(size_t max_partition_size)
      : max_partition_size_(max_partition_size) {}

  void addDataPoint(const DataPoint &data) {
    data_.push_back(data);
    if (data_.size() > max_partition_size_) {
      automatePartitionMaintenance();
    }
  }

  // Automate partition maintenance: Sort data, remove oldest partitions, and
  // ensure data is evenly distributed
  void automatePartitionMaintenance() {
    // Sort data based on some criteria (e.g., timestamp)
    std::sort(
        data_.begin(), data_.end(), [](const DataPoint &a, const DataPoint &b) {
          return a[0] <
                 b[0]; // Assuming the first element represents the timestamp
        });

    const size_t num_partitions = data_.size() / max_partition_size_;
    size_t kept_data_size = num_partitions * max_partition_size_;

    // Remove oldest partitions
    data_.erase(data_.begin(), data_.begin() + (data_.size() - kept_data_size));
  }

  size_t getNumDataPoints() const { return data_.size(); }
};

int main() {
  const size_t max_partition_size = 100;
  std::unique_ptr<IoTDataManager> dataManager =
      std::make_unique<IoTDataManager>(max_partition_size);

  // Generate sample data and add it to the manager
  for (int i = 0; i < 1000; ++i) {
    IoTDataManager::DataPoint data{static_cast<float>(i),
                                   static_cast<float>(i * 2),
                                   static_cast<float>(i * 3)};
    dataManager->addDataPoint(data);
  }

  std::cout << "Number of data points: " << dataManager->getNumDataPoints()
            << std::endl;

  return 0;
}