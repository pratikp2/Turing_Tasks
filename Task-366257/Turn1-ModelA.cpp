#include <iostream>
#include <vector>

// Predicate to filter data points
bool isAboveThreshold(int value, int threshold) {
    return value > threshold;
}

int main() {
    // Example sensor data
    std::vector<int> sensorData = {20, 30, 50, 10, 25, 70, 60, 40};
    int threshold = 50;

    // Step 1: Remove elements above the threshold using std::remove_if + std::erase
    sensorData.erase(std::remove_if(sensorData.begin(), sensorData.end(),
                                     std::bind(isAboveThreshold, std::placeholders::_1, threshold)),
                      sensorData.end());

    // Output filtered data
    std::cout << "Filtered Sensor Data: ";
    for (int value : sensorData) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}