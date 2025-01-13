#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <vector>
#include <random>

const int DEFAULT_ROWS = 10;        // Increased to 10 rows
const int DEFAULT_COLS = 10;        // Increased to 10 columns

void printArray(int* array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(3) << *(array + i * cols + j) << " ";
        }
        std::cout << std::endl;
    }
}

void extractSlice(const int* mriData, int startRow, int startCol, int sliceRows, int sliceCols, std::unique_ptr<int[]>& sliceData) {
    if (startRow < 0 || startCol < 0 || 
        startRow + sliceRows > DEFAULT_ROWS || 
        startCol + sliceCols > DEFAULT_COLS) {
        throw std::out_of_range("Slice boundaries are out of range.");
    }
    sliceData.reset(new int[sliceRows * sliceCols]);
    for (int i = 0; i < sliceRows; ++i) {
        for (int j = 0; j < sliceCols; ++j) {
            *(sliceData.get() + i * sliceCols + j) = *(mriData + (startRow + i) * DEFAULT_COLS + (startCol + j));
        }
    }
}

void enhanceSlice(int* sliceData, int sliceRows, int sliceCols) {
    for (int i = 0; i < sliceRows; ++i) {
        for (int j = 0; j < sliceCols; ++j) {
            *(sliceData + i * sliceCols + j) *= 2;
        }
    }
}

void processMRIDataset(int datasetNumber) {
    std::cout << "Processing MRI Dataset " << datasetNumber << ":\n";
    std::unique_ptr<int[]> mriData(new int[DEFAULT_ROWS * DEFAULT_COLS]);

    // Randomly generating dataset for testing
    std::srand(static_cast<unsigned>(std::time(0)));
    for (int r = 0; r < DEFAULT_ROWS; ++r) {
        for (int c = 0; c < DEFAULT_COLS; ++c) {
            // Generate random MRI data values (from 0 to 99)
            mriData[r * DEFAULT_COLS + c] = std::rand() % 100;
        }
    }

    std::cout << "Original MRI Data:\n";
    printArray(mriData.get(), DEFAULT_ROWS, DEFAULT_COLS);

    // Testing various slices
    struct TestCase {
        int startRow;
        int startCol;
        int sliceRows;
        int sliceCols;
    };

    // Define test cases for slicing
    std::vector<TestCase> testCases = {
        {1, 1, 3, 3},   // Valid case
        {8, 8, 2, 2},   // Near bottom right corner valid case
        {0, 0, 5, 5},   // Full slice
        {5, 5, 5, 5},   // Out of bounds
        {-1, 0, 3, 3},  // Out of bounds (negative start row)
        {1, 1, 0, 1},   // Zero height slice
        {0, 0, 1, 0},   // Zero width slice
        {9, 9, 1, 1},   // Barely valid case (slice should just get single pixel)
        {3, 3, 7, 7},   // Out of bounds (so large it spills over)
    };

    for (const auto& testCase : testCases) {
        std::cout << "\nTesting Slice: Start(" << testCase.startRow << ", " << testCase.startCol << ") Size(" 
                  << testCase.sliceRows << "x" << testCase.sliceCols << ")\n";

        std::unique_ptr<int[]> sliceData;
        try {
            extractSlice(mriData.get(), testCase.startRow, testCase.startCol, testCase.sliceRows, testCase.sliceCols, sliceData);
            std::cout << "Extracted Slice:\n";
            printArray(sliceData.get(), testCase.sliceRows, testCase.sliceCols);

            // Enhance the slice
            enhanceSlice(sliceData.get(), testCase.sliceRows, testCase.sliceCols);
            std::cout << "Enhanced Slice:\n";
            printArray(sliceData.get(), testCase.sliceRows, testCase.sliceCols);

            // Copy enhanced slice back to original MRI data
            for (int i = 0; i < testCase.sliceRows; ++i) {
                for (int j = 0; j < testCase.sliceCols; ++j) {
                    *(mriData.get() + (testCase.startRow + i) * DEFAULT_COLS + (testCase.startCol + j)) = sliceData[i * testCase.sliceCols + j];
                }
            }

            std::cout << "Modified MRI Data after enhancing slice:\n";
            printArray(mriData.get(), DEFAULT_ROWS, DEFAULT_COLS);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    int numDatasets = 1;  // Change to process more datasets if needed
    for (int i = 1; i <= numDatasets; ++i) {
        processMRIDataset(i);
    }

    return 0;
}
