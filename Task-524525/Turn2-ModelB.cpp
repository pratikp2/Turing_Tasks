#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class SensorCalibration {
public:
    // ... (Original constructor, destructor, and operator() remained the same)

    // Transpose the 3D array (swap sensorID and timeInterval dimensions)
    void transpose() {
        for (int k = 0; k < measurementTypes; ++k) {
            for (int i = 0; i < sensors; ++i) {
                for (int j = i+1; j < sensors; ++j) {
                    float temp = operator()(i, k, j);
                    operator()(i, k, j) = operator()(j, k, i);
                    operator()(j, k, i) = temp;
                }
            }
        }
    }

    // Simple function to demonstrate element access for the sake of performance discussion
    void applyOffsetToAllElements(float offset) {
        for (int i = 0; i < sensors; ++i) {
            for (int j = 0; j < timeIntervals; ++j) {
                for (int k = 0; k < measurementTypes; ++k) {
                    operator()(i, j, k) += offset;
                }
            }
        }
    }

    // Pointer-based function to apply offset to all elements
    void applyOffsetToAllElementsWithPointers(float offset) {
        float* tempData = data[0][0]; // Start of the data array
        for (size_t i = 0; i < sensors * timeIntervals * measurementTypes; ++i) {
            *tempData += offset;
            tempData++;
        }
    }
};

int main() {
    const int numSensors = 10;
    const int numTimeIntervals = 20;
    const int numMeasurementTypes = 3;

    SensorCalibration calib(numSensors, numTimeIntervals, numMeasurementTypes);

    // Initialize the calibration data
    for (int i = 0; i < numSensors; ++i) {
        for (int j = 0; j < numTimeIntervals; ++j) {
            for (int k = 0; k < numMeasurementTypes; ++k) {
                calib(i, j, k) = static_cast<float>(i * j * k + rand() % 10);
            }
        }
    }

    // Perform a transpose operation to demonstrate array manipulation
    std::cout << "\nOriginal Array:" << std::endl;
    calib.print();

    std::cout << "\nTransposed Array:" << std::endl;
    calib.transpose();
    calib.print();

    // Demonstrate element access optimization using pointers
    std::cout << "\nApplying offset using nested loops..." << std::endl;
    float offsetValue = 5.0f;
    const auto startTime = std::clock();
    calib.applyOffsetToAllElements(offsetValue);
    const auto endTime = std::clock();
    std::cout << "Time taken: " << static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << std::endl;

    std::cout << "\nApplying offset using pointers..." << std::endl;
    startTime = std::clock();
    calib.applyOffsetToAllElementsWithPointers(offsetValue);
    endTime = std::clock();
    std::cout << "Time taken: " << static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}
