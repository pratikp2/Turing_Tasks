#include <iostream>
#include <iomanip>
#include <stdexcept>

const int ROWS = 5;        // Number of rows in the MRI data
const int COLS = 5;        // Number of columns in the MRI data

// Function to print a 2D array
void printArray(int* array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(3) << *(array + i * COLS + j) << " ";
        }
        std::cout << std::endl;
    }
}

// Function to extract a slice from the MRI data
void extractSlice(const int* mriData, int startRow, int startCol, int sliceRows, int sliceCols, int* sliceData) {
    // Validate parameters to prevent out-of-bounds access
    if (startRow < 0 || startCol < 0 || 
        startRow + sliceRows > ROWS || 
        startCol + sliceCols > COLS) {
        throw std::out_of_range("Slice boundaries are out of range.");
    }

    for (int i = 0; i < sliceRows; ++i) {
        for (int j = 0; j < sliceCols; ++j) {
            *(sliceData + i * sliceCols + j) = *(mriData + (startRow + i) * COLS + (startCol + j));
        }
    }
}

int main() {
    // Simulated MRI data (5x5 for simplicity)
    int mriData[ROWS][COLS] = {
        { 1,  2,  3,  4,  5 },
        { 6,  7,  8,  9, 10 },
        {11, 12, 13, 14, 15 },
        {16, 17, 18, 19, 20 },
        {21, 22, 23, 24, 25 }
    };

    // Pointer to the 2D MRI data
    const int* pMriData = &mriData[0][0];

    // Define the slice parameters
    int startRow = 1; // Starting row for the slice
    int startCol = 1; // Starting column for the slice
    int sliceRows = 3; // Number of rows in the slice
    int sliceCols = 3; // Number of columns in the slice

    // Array to hold the slice
    int sliceData[sliceRows * sliceCols];

    try {
        // Extract the slice
        extractSlice(pMriData, startRow, startCol, sliceRows, sliceCols, sliceData);

        // Print the original MRI data
        std::cout << "Original MRI Data:" << std::endl;
        printArray(pMriData, ROWS, COLS);

        // Print the extracted slice
        std::cout << "\nExtracted Slice:" << std::endl;
        printArray(sliceData, sliceRows, sliceCols);
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
