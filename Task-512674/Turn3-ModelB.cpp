#include <iostream>
#include <iomanip>
#include <cassert>

const int MRI_ROWS = 100;   // Assuming a larger MRI dataset
const int MRI_COLS = 128;
const int MRI_SLICES = 30;  // Assuming 30 slices in the MRI data

// Function to print a 2D array
void printArray(const int* array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(3) << *(array + i * cols + j) << " ";
        }
        std::cout << std::endl;
    }
}

// Function to slice a specific region from the MRI image array
void extractSlice(const int* mriData, int sliceIndex, int startRow, int startCol, int sliceRows, int sliceCols, int* sliceData) {
    assert(sliceIndex >= 0 && sliceIndex < MRI_SLICES);
    assert(startRow >= 0 && startRow < MRI_ROWS);
    assert(startCol >= 0 && startCol < MRI_COLS);
    assert(startRow + sliceRows <= MRI_ROWS);
    assert(startCol + sliceCols <= MRI_COLS);

    int* sliceBase = &mriData[sliceIndex * MRI_ROWS * MRI_COLS];

    for (int i = 0; i < sliceRows; ++i) {
        for (int j = 0; j < sliceCols; ++j) {
            *(sliceData + i * sliceCols + j) = *(sliceBase + (startRow + i) * MRI_COLS + (startCol + j));
        }
    }
}

int main() {
    // Simulated MRI data (assuming 3D data with 100 rows, 128 columns, and 30 slices)
    // In a real application, you'd allocate memory dynamically or load data from a file.
    int mriData[MRI_SLICES * MRI_ROWS * MRI_COLS];

    // Initialize the MRI data with random values (for demonstration purposes)
    for (int i = 0; i < MRI_SLICES * MRI_ROWS * MRI_COLS; ++i) {
        mriData[i] = i % 100;
    }

    // Define the slice parameters
    int sliceIndex = 15;   // Slice index to extract
    int startRow = 20;      // Starting row for the slice
    int startCol = 30;      // Starting column for the slice
    int sliceRows = 50;     // Number of rows in the slice
    int sliceCols = 60;     // Number of columns in the slice

    // Array to hold the slice
    int sliceData[sliceRows * sliceCols];

    // Extract the slice
    extractSlice(mriData, sliceIndex, startRow, startCol, sliceRows, sliceCols, sliceData);

    // Print the extracted slice
    std::cout << "Extracted Slice from MRI Slice " << sliceIndex << ":" << std::endl;
    printArray(sliceData, sliceRows, sliceCols);

    // ... Further processing of the slice can be done here ...

    return 0;
}
