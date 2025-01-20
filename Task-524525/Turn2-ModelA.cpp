#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>  // for memset in reset function

class SensorCalibration {
public:
    SensorCalibration(int sensors, int timeIntervals, int measurementTypes) 
        : sensors(sensors), timeIntervals(timeIntervals), measurementTypes(measurementTypes) {
        // Allocate memory for a 3D array as a contiguous block
        int totalSize = sensors * timeIntervals * measurementTypes;
        data = new float[totalSize];
    }

    ~SensorCalibration() {
        delete[] data;  // Deallocate memory
    }

    // Accessor using pointer arithmetic
    float& at(int sensorId, int timeInterval, int measurementType) {
        return *(data + (sensorId * timeIntervals * measurementTypes + timeInterval * measurementTypes + measurementType));
    }

    // Reset the calibration data
    void reset() {
        std::memset(data, 0, sensors * timeIntervals * measurementTypes * sizeof(float));  // Reset to zeros
    }

    // Print function to display current calibration data
    void print() const {
        for (int i = 0; i < sensors; ++i) {
            std::cout << "Sensor ID: " << i << std::endl;
            for (int j = 0; j < timeIntervals; ++j) {
                for (int k = 0; k < measurementTypes; ++k) {
                    std::cout << std::fixed << std::setprecision(2)
                              << "data[" << i << "][" << j << "][" << k << "] = "
                              << at(i, j, k) << std::endl;
                }
            }
        }
    }

private:
    int sensors;
    int timeIntervals;
    int measurementTypes;
    float* data;  // 1D array acting as a 3D array
};

int main() {
    const int numSensors = 3;
    const int numTimeIntervals = 5;
    const int numMeasurementTypes = 2;

    SensorCalibration calib(numSensors, numTimeIntervals, numMeasurementTypes);

    // Example: Initialize the calibration data using pointer arithmetic
    for (int i = 0; i < numSensors; ++i) {
        for (int j = 0; j < numTimeIntervals; ++j) {
            for (int k = 0; k < numMeasurementTypes; ++k) {
                calib.at(i, j, k) = static_cast<float>(i + j + k);  // Example initialization
            }
        }
    }

    // Print the calibration data
    calib.print();

    // Reset the calibration data
    calib.reset();
    std::cout << "After reset:" << std::endl;
    calib.print();

    return 0;
}
