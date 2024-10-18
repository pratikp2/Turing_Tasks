#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

class IoTDataManager {
public:
  using DataPoint = std::vector<float>;
  using DataContainer = std::vector<DataPoint>;

private:
  DataContainer data_;
  size_t max_partition_size_;
  float partition_threshold_;

public:
  IoTDataManager(size_t max_partition_size, float partition_threshold)
      : max_partition_size_(max_partition_size),
        partition_threshold_(partition_threshold) {}

  void addDataPoint(const DataPoint &data) {
    data_.push_back(data);
    if (shouldAutomatePartitionMaintenance()) {
      automatePartitionMaintenance();
    }
  }

  bool shouldAutomatePartitionMaintenance() const {
    // Check if the data size has exceeded the maximum partition size or if the
    // data distribution is skewed
    return data_.size() > max_partition_size_ ||
           calculatePartitionSkew() > partition_threshold_;
  }

  void automatePartitionMaintenance() {
    // Sort data based on some criteria (e.g., timestamp)
    std::sort(
        data_.begin(), data_.end(), [](const DataPoint &a, const DataPoint &b) {
          return a[0] <
                 b[0]; // Assuming the first element represents the timestamp
        });

    const size_t num_partitions = data_.size() / max_partition_size_;
    size_t kept_data_size = num_partitions * max_partition_size_;

    // Remove oldest partitions to ensure a more balanced distribution
    data_.erase(data_.begin(), data_.begin() + (data_.size() - kept_data_size));
  }

  float calculatePartitionSkew() const {
    if (data_.empty())
      return 0.0;

    const size_t num_partitions = data_.size() / max_partition_size_;
    std::vector<size_t> partition_sizes(num_partitions, 0);

    for (size_t i = 0; i < data_.size(); ++i) {
      const size_t partition_index = i / max_partition_size_;
      partition_sizes[partition_index]++;
    }

    const float average_size =
        static_cast<float>(data_.size()) / num_partitions;
    float skew = 0.0;
    for (size_t size : partition_sizes) {
      const float diff = static_cast<float>(size) - average_size;
      skew += diff * diff;
    }

    return std::sqrt(skew) / average_size;
  }

  size_t getNumDataPoints() const { return data_.size(); }
};

int main() {
  const size_t max_partition_size = 100;
  const float partition_threshold = 0.1; // Adjust the threshold as needed
  std::unique_ptr<IoTDataManager> dataManager =
      std::make_unique<IoTDataManager>(max_partition_size, partition_threshold);

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