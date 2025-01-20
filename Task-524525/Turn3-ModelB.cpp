#include <iostream>

void createAndPopulate3DArray(int sensorId, int timeInterval, int measurementType, float**& result) {
    try {
        // Calculate the total number of elements in the 3D array
        int totalElements = sensorId * timeInterval * measurementType;

        // Check for non-positive dimensions
        if (sensorId <= 0 || timeInterval <= 0 || measurementType <= 0) {
            throw std::invalid_argument("Dimensions must be positive integers.");
        }

        // Dynamically allocate memory for the 3D array
        result = new float*[sensorId];
        for (int i = 0; i < sensorId; ++i) {
            result[i] = new float[timeInterval];
            for (int j = 0; j < timeInterval; ++j) {
                result[i][j] = new float[measurementType];
            }
        }

        // Populate the 3D array using pointer arithmetic
        for (int i = 0; i < sensorId; ++i) {
            for (int j = 0; j < timeInterval; ++j) {
                float* ptr = result[i][j];  // Get a pointer to the start of the 2D slice
                for (int k = 0; k < measurementType; ++k) {
                    *ptr = static_cast<float>(i * timeInterval * measurementType + j * measurementType + k);
                    ++ptr;  // Move to the next element in the 2D slice
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // If an exception occurs, deallocate any memory that was already allocated
        if (result) {
            for (int i = 0; i < sensorId; ++i) {
                if (result[i]) {
                    for (int j = 0; j < timeInterval; ++j) {
                        delete[] result[i][j];
                    }
                    delete[] result[i];
                }
            }
            delete[] result;
            result = nullptr;
        }
        return;
    }
}

void deallocate3DArray(float**& result) {
    if (result) {
        for (int i = 0; i < *(&result)[0]; ++i) {
            if (result[i]) {
                for (int j = 0; j < *(&result + 1)[i]; ++j) {
                    delete[] result[i][j];
                }
                delete[] result[i];
            }
        }
        delete[] result;
        result = nullptr;
    }
}

int main() {
    const int sensors = 2;
    const int timeIntervals = 3;
    const int measurementTypes = 4;

    float** calibrationData = nullptr;

    try {
        createAndPopulate3DArray(sensors, timeIntervals, measurementTypes, calibrationData);

        // Display the calibration data
        for (int i = 0; i < sensors; ++i) {
            for (int j = 0; j < timeIntervals; ++j) {
                for (int k = 0; k < measurementTypes; ++k) {
                    std::cout << calibrationData[i][j][k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Deallocate the memory
    deallocate3DArray(calibrationData);

    return 0;
}
