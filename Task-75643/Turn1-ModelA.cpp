#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <ratio>
#include <chrono>

// Function to perform resampling
std::vector<double> resample(const std::vector<double>& data, size_t new_size) {
   if (data.empty() || new_size <= 0) {
    return {};
   }

   double step = static_cast<double>(data.size()) / new_size;
   std::vector<double> resampled_data(new_size);

   for (size_t i = 0; i < new_size; ++i) {
    double index = i * step;
    size_t low = static_cast<size_t>(std::floor(index));
    size_t high = static_cast<size_t>(std::ceil(index));

    if (low == high) {
      resampled_data[i] = data[low];
    } else {
      double alpha = index - low;
      resampled_data[i] = data[low] + alpha * (data[high] - data[low]);
    }
   }

   return resampled_data;
}

// Function to perform time shifting
std::vector<double> timeShift(const std::vector<double>& data, int shift) {
   std::vector<double> shifted_data = data;
   if (shift != 0) {
    if (shift > 0) {
      shifted_data.insert(shifted_data.begin(), shift, 0);
      shifted_data.resize(data.size());
    } else {
      shifted_data.erase(shifted_data.begin(), std::abs(shift));
      shifted_data.insert(shifted_data.end(), std::abs(shift), 0);
    }
   }
   return shifted_data;
}
// Function to calculate the moving average
std::vector<double> movingAverage(const std::vector<double>& data, int window_size) {
   std::vector<double> ma_data;

   if (data.empty() || window_size <= 0) {
    return ma_data;
   }

   for (size_t i = 0; i < data.size(); ++i) {
    int start = std::max(0, static_cast<int>(i) - (window_size - 1) / 2);
    int end = std::min(static_cast<int>(data.size()) - 1, static_cast<int>(i) + (window_size - 1) / 2);

    double sum = std::accumulate(data.begin() + start, data.begin() + end + 1, 0.0);
    ma_data.push_back(sum / (end - start + 1));
   }

   return ma_data;
}

int main() {
   // Example time series data
   std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

   // Resampling example
   size_t new_size = 5;
   std::vector<double> resampled_data = resample(data, new_size);
   std::cout << "Resampled data: ";
   for (const double& value : resampled_data) {
    std::cout << value << " ";
   }
   std::cout << std::endl;

   // Time shifting example
   int shift = 2;
   std::vector<double> shifted_data = timeShift(data, shift);
   std::cout << "Time shifted data: ";
   for (const double& value : shifted_data) {
    std::cout << value << " ";
   }
   std::cout << std::endl;

   // Moving average example
   int window_size = 3;
   std::vector<double> ma_data = movingAverage(data, window_size);
   std::cout << "Moving average data: ";
   for (const double& value : ma_data) {
    std::cout << value << " ";
   }
   std::cout << std::endl;
   return 0;
}