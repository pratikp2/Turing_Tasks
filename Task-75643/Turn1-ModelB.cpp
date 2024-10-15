#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

// Sample time-series data (distance traveled in each time step)
const std::vector<double> time_series_data = {2.5, 3.0, 3.6, 4.1, 4.8, 5.2, 5.5, 6.0, 6.3, 6.8};

// Data Downsampling: Reduce data points by taking the average of consecutive 'window_size' points
std::vector<double> downsampleData(const std::vector<double>& data, int window_size) {
    std::vector<double> downsampled_data;
    if (window_size <= 0 || data.empty()) {
        return downsampled_data;
    }

    for (size_t i = 0; i < data.size(); i += window_size) {
        double sum = std::accumulate(data.begin() + i, data.begin() + std::min(i + window_size, data.size()), 0.0);
        downsampled_data.push_back(sum / std::min(window_size, static_cast<int>(data.size() - i)));
    }
    return downsampled_data;
}

// Data Discretization: Convert data into discrete intervals
std::vector<int> discretizeData(const std::vector<double>& data, double interval_size) {
    std::vector<int> discretized_data;
    if (interval_size <= 0 || data.empty()) {
        return discretized_data;
    }

    for (double value : data) {
        discretized_data.push_back(static_cast<int>(std::floor(value / interval_size)));
    }
    return discretized_data;
}

// Time Series Segmentation: Divide data into segments of equal size
std::vector<std::vector<double>> segmentData(const std::vector<double>& data, int segment_size) {
    std::vector<std::vector<double>> segments;
    if (segment_size <= 0 || data.empty()) {
        return segments;
    }

    for (size_t i = 0; i < data.size(); i += segment_size) {
        size_t end_index = std::min(i + segment_size, data.size());
        segments.push_back(std::vector<double>(data.begin() + i, data.begin() + end_index));
    }
    return segments;
}

// Differencing: Calculate the differences between consecutive data points
std::vector<double> differentiateData(const std::vector<double>& data) {
    std::vector<double> differentiated_data;
    if (data.size() < 2) {
        return differentiated_data;
    }

    for (size_t i = 1; i < data.size(); ++i) {
        differentiated_data.push_back(data[i] - data[i - 1]);
    }
    return differentiated_data;
}

// Scaling: Normalize data to have a mean of 0 and a standard deviation of 1
std::vector<double> scaleData(const std::vector<double>& data) {
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = std::inner_product(data.begin(), data.end(), data.begin(), 0.0) / data.size() - mean * mean;
    double std_dev = std::sqrt(variance);

    std::vector<double> scaled_data;
    for (double value : data) {
        scaled_data.push_back((value - mean) / std_dev);
    }
    return scaled_data;
}

int main() {
    // Original Time Series Data
    std::cout << "Original Time Series Data: " << std::endl;
    for (double value : time_series_data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Data Downsampling (window size = 3)
    int downsampling_window_size = 3;
    std::vector<double> downsampled_data = downsampleData(time_series_data, downsampling_window_size);
    std::cout << "Downsampled Data (window size = " << downsampling_window_size << "): " << std::endl;
    for (double value : downsampled_data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Data Discretization (interval size = 0.5)
    double discretization_interval_size = 0.5;
    std::vector<int> discretized_data = discretizeData(time_series_data, discretization_interval_size);
    std::cout << "Discretized Data (interval size = " << discretization_interval_size << "): " << std::endl;
    for (int value : discretized_data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Time Series Segmentation (segment size = 3)
    int segmentation_segment_size = 3;
    std::vector<std::vector<double>> segments = segmentData(time_series_data, segmentation_segment_size);
    std::cout << "Time Series Segments (segment size = " << segmentation_segment_size << "): " << std::endl;
    for (const std::vector<double>& segment : segments) {
        for (double value : segment) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    // Differencing
    std::vector<double> differentiated_data = differentiateData(time_series_data);
    std::cout << "Differentiated Data: " << std::endl;
    for (double value : differentiated_data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Scaling
    std::vector<double> scaled_data = scaleData(time_series_data);
    std::cout << "Scaled Data: " << std::endl;
    for (double value : scaled_data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}