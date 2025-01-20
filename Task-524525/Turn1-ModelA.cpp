#include <iostream>
#include <iomanip>
#include <cstdlib>

class SensorCalibration {
public:
    SensorCalibration(int sensors, int timeIntervals, int measurementTypes) 
        : sensors(sensors), timeIntervals(timeIntervals), measurementTypes(measurementTypes) {
        // Allocate memory for a 3D array
        data = new float**[sensors];
        for (int i = 0; i < sensors; ++i) {
            data[i] = new float*[timeIntervals];
            for (int j = 0; j < timeIntervals; ++j) {
                data[i][j] = new float[measurementTypes];
            }
        }
    }

    ~SensorCalibration() {
        // Deallocate memory
        for (int i = 0; i < sensors; ++i) {
            for (int j = 0; j < timeIntervals; ++j) {
                delete[] data[i][j];
            }
            delete[] data[i];
        }
        delete[] data;
    }

    // Accessor using pointer arithmetic
    float& operator()(int sensorId, int timeInterval, int measurementType) {
        return *(*(*(data + sensorId) + timeInterval) + measurementType);
    }

    void print() {
        for (int i = 0; i < sensors; ++i) {
            std::cout << "Sensor ID: " << i << std::endl;
            for (int j = 0; j < timeIntervals; ++j) {
                for (int k = 0; k < measurementTypes; ++k) {
                    std::cout << std::fixed << std::setprecision(2)
                              << "data[" << i << "][" << j << "][" << k << "] = "
                              << operator()(i, j, k) << std::endl;
                }
            }
        }
    }

private:
    int sensors;
    int timeIntervals;
    int measurementTypes;
    float*** data;  // 3D array
};

int main() {
    const int numSensors = 3;
    const int numTimeIntervals = 5;
    const int numMeasurementTypes = 2;

    SensorCalibration calib(numSensors, numTimeIntervals, numMeasurementTypes);

    // Example: Initialize the calibration data
    for (int i = 0; i < numSensors; ++i) {
        for (int j = 0; j < numTimeIntervals; ++j) {
            for (int k = 0; k < numMeasurementTypes; ++k) {
                calib(i, j, k) = static_cast<float>(i * j * k);  // Example initialization
            }
        }
    }

    // Print the calibration data
    calib.print();

    return 0;
}
