#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <atomic>
#include <chrono>

// Function to simulate computer vision processing and generate time-series data
std::vector<double> generateTimeSeriesData() {
  std::vector<double> data;
  for (int i = 0; i < 100; ++i) {
    // Simulate data generation with some noise
    data.push_back(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX)) * 10 + 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return data;
}

// Apply moving average to a time series data
std::vector<double> applyMovingAverage(const std::vector<double>& data, int windowSize)
{
  std::vector<double> result;

  if (data.empty() || windowSize <= 0) {
    return result;
  }

  int dataSize = static_cast<int>(data.size());
  for (int i = 0; i < dataSize; ++i)
  {
    int startIndex = std::max(0, i - (windowSize - 1) / 2);
    int endIndex = std::min(dataSize - 1, i + (windowSize - 1) / 2);

    double sum = std::accumulate(data.begin() + startIndex, data.begin() + endIndex + 1, 0.0);
    result.push_back(sum / (endIndex - startIndex + 1));
  }

  return result;
}

int main() {
  const int windowSize = 5; // Window size for moving average

  std::vector<double> timeSeriesData = generateTimeSeriesData();

  // Apply moving average to the time-series data
  std::vector<double> smoothedData = applyMovingAverage(timeSeriesData, windowSize);

  // Display the original and smoothed data
  for (size_t i = 0; i < timeSeriesData.size(); i++) {
    std::cout << "Original Data: " << timeSeriesData[i] << " Smoothed Data: " << smoothedData[i] << std::endl;
  }

  return 0;
}