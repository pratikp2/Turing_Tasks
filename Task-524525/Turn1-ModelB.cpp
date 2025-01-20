#include<iostream>
 using namespace std;
 
 const int SENSOR_COUNT = 5;    // Number of sensors
 const int TIME_INTERVALS = 10; // Number of time intervals
 const int MEASUREMENT_TYPES = 3; // Number of measurement types
 
 typedef double DataType;

 int main() {
    // Allocate memory for the 3D matrix using a single array
    DataType* matrix = new DataType[SENSOR_COUNT * TIME_INTERVALS * MEASUREMENT_TYPES];

    // Calculate the dimensions of the lower levels of the 3D matrix
    const int timeIntervalStride = MEASUREMENT_TYPES;
    const int measurementTypeStride = TIME_INTERVALS;

    // Initialize the matrix
    for (int sensor = 0; sensor < SENSOR_COUNT; ++sensor) {
        for (int time = 0; time < TIME_INTERVALS; ++time) {
            for (int measure = 0; measure < MEASUREMENT_TYPES; ++measure) {
                int index = sensor * timeIntervalStride * measurementTypeStride 
                       + time * measurementTypeStride + measure;
              
                matrix[index] = (sensor + 1) * (time + 1) * (measure + 1);
                // You can uncomment the below line if you want to display the initialized matrix.
                //cout << "matrix[" << sensor << "][" << time << "][" << measure << "] = " << matrix[index] << endl;
            }
        }
    }

    // Accessing and updating element using pointer arithmetic
    int sensorToUpdate = 2;
    int timeToUpdate = 3;
    int measureToUpdate = 1;

    DataType updatedValue = 100.0;

    int indexToUpdate = sensorToUpdate * timeIntervalStride * measurementTypeStride
                       + timeToUpdate * measurementTypeStride + measureToUpdate;

    DataType* elementToUpdate = &matrix[indexToUpdate];

    //Access 
    cout << "Old value : " << *elementToUpdate << endl;

    // Update
    *elementToUpdate = updatedValue;

    cout << "Updated value at " << "matrix[" << sensorToUpdate << "][" 
        << timeToUpdate << "][" << measureToUpdate << "]: " << *elementToUpdate << endl;

     // Remember to deallocate the dynamically allocated memory
    delete[] matrix;
    return 0;
}
