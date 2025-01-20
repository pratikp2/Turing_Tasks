#include <iostream>

float calculateSum3DArray(const float* data, int sensors, int timeIntervals, int measurementTypes) {
    if (data == nullptr) {
        std::cerr << "Error: Invalid input. The pointer to the 3D array is null." << std::endl;
        return 0.0f;
    }

    if (sensors <= 0 || timeIntervals <= 0 || measurementTypes <= 0) {
        std::cerr << "Error: Invalid input. Dimensions of the 3D array must be positive integers." << std::endl;
        return 0.0f;
    }

    int totalSize = sensors * timeIntervals * measurementTypes;
    float sum = 0.0f;

    // Calculate the sum using pointer arithmetic
    for (int i = 0; i < totalSize; ++i) {
        sum += *(data + i);
    }

    return sum;
}

int main() {
    const int numSensors = 3;
    const int numTimeIntervals = 4;
    const int numMeasurementTypes = 2;

    // Create and populate the 3D array
    float* calibrationData = createAndPopulate3DArray(numSensors, numTimeIntervals, numMeasurementTypes);

    if (calibrationData) {
        // Calculate the sum of all elements
        float sum = calculateSum3DArray(calibrationData, numSensors, numTimeIntervals, numMeasurementTypes);
        std::cout << "Sum of all elements in the 3D array: " << sum << std::endl;

        // Deallocate the memory
        deallocate3DArray(calibrationData);
    }

    return 0;
}
