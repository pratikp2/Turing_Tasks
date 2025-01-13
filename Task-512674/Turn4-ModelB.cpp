#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <vector>

const int DEFAULT_ROWS = 5;        // Default number of rows in MRI data
const int DEFAULT_COLS = 5;        // Default number of columns in MRI data

void printArray(int* array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(3) << *(array + i * cols + j) << " ";
        }
        std::cout << std::endl;
    }
}

// Function to extract a slice from the MRI data
void extractSlice(const int* mriData, int startRow, int startCol, int sliceRows, int sliceCols, std::unique_ptr<int[]>& sliceData) {
    // Validate parameters
    if (startRow < 0 || startCol < 0 || 
        startRow + sliceRows > DEFAULT_ROWS || 
        startCol + sliceCols > DEFAULT_COLS) {
        throw std::out_of_range("Slice boundaries are out of range.");
    }

    // Allocate memory for the slice
    sliceData.reset(new int[sliceRows * sliceCols]);

    for (int i = 0; i < sliceRows; ++i) {
        for (int j = 0; j < sliceCols; ++j) {
            *(sliceData.get() + i * sliceCols + j) = *(mriData + (startRow + i) * DEFAULT_COLS + (startCol + j));
        }
    }
}

// Function to enhance the slice data by doubling its values
void enhanceSlice(int* sliceData, int sliceRows, int sliceCols) {
    for (int i = 0; i < sliceRows; ++i) {
        for (int j = 0; j < sliceCols; ++j) {
            *(sliceData + i * sliceCols + j) *= 2;
        }
    }
}

void processMRIDataset(int numDatasets) {
    std::cout << "Processing MRI Dataset(s):" << std::endl;
    try {
        for (int i = 0; i < numDatasets; ++i) {
            // Simulated MRI data for each dataset (can be loaded from files in a real application)
            std::unique_ptr<int[]> mriData(new int[DEFAULT_ROWS * DEFAULT_COLS]);

            for (int r = 0; r < DEFAULT_ROWS; ++r) {
                for (int c = 0; c < DEFAULT_COLS; ++c) {
                    // Generate random test data
                    mriData[r * DEFAULT_COLS + c] = (r * 10) + c + (i * 100);
                }
            }

            std::cout << "\nDataset " << i + 1 << ":" << std::endl;
            std::cout << "Original MRI Data:" << std::endl;
            printArray(mriData.get(), DEFAULT_ROWS, DEFAULT_COLS);

            // Define the slice parameters
            int startRow = 1;
            int startCol = 1;
            int sliceRows = 3;
            int sliceCols = 3;

            // Extract the slice
            std::unique_ptr<int[]> sliceData;
            extractSlice(mriData.get(), startRow, startCol, sliceRows, sliceCols, sliceData);

            // Print the extracted slice
            std::cout << "\nExtracted Slice:" << std::endl;
            printArray(sliceData.get(), sliceRows, sliceCols);

            // Apply enhancement to the slice
            enhanceSlice(sliceData.get(), sliceRows, sliceCols);

            // Copy enhanced slice back to original MRI data
            for (int i = 0; i < sliceRows; ++i) {
                for (int j = 0; j < sliceCols; ++j) {
                    *(mriData.get() + (startRow + i) * DEFAULT_COLS + (startCol + j)) = sliceData[i * sliceCols + j];
                }
            }

            // Print the modified MRI data
            std::cout << "\nModified MRI Data after enhancing slice:" << std::endl;
            printArray(mriData.get(), DEFAULT_ROWS, DEFAULT_COLS);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    int numDatasets = 2;
    processMRIDataset(numDatasets);

    return 0;
}
