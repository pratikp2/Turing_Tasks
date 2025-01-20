#include <iostream>
#include <iomanip>

float* createAndPopulate3DArray(int sensors, int timeIntervals, int measurementTypes) {
    // Allocate memory for a 3D array as a contiguous block
    int totalSize = sensors * timeIntervals * measurementTypes;
    float* data = new float[totalSize];

    // Populate the array using pointer arithmetic
    for (int i = 0; i < sensors; ++i) {
        for (int j = 0; j < timeIntervals; ++j) {
            for (int k = 0; k < measurementTypes; ++k) {
                *(data + (i * timeIntervals * measurementTypes + j * measurementTypes + k)) = 
                    static_cast<float>(i + j + k);
            }
        }
    }

    return data;  // Return the pointer to the allocated memory
}

void deallocate3DArray(float* data) {
    delete[] data;  // Deallocate the memory
}

void print3DArray(float* data, int sensors, int timeIntervals, int measurementTypes) {
    for (int i = 0; i < sensors; ++i) {
        std::cout << "Sensor ID: " << i << std::endl;
        for (int j = 0; j < timeIntervals; ++j) {
            for (int k = 0; k < measurementTypes; ++k) {
                std::cout << std::fixed << std::setprecision(2)
                          << "data[" << i << "][" << j << "][" << k << "] = "
                          << *(data + (i * timeIntervals * measurementTypes + j * measurementTypes + k)) << std::endl;
            }
        }
    }
}

int main() {
    const int numSensors = 3;
    const int numTimeIntervals = 4;
    const int numMeasurementTypes = 2;

    // Create and populate the 3D array
    float* calibrationData = createAndPopulate3DArray(numSensors, numTimeIntervals, numMeasurementTypes);

    // Print the populated data
    print3DArray(calibrationData, numSensors, numTimeIntervals, numMeasurementTypes);

    // Deallocate the memory
    deallocate3DArray(calibrationData);

    return 0;
}
