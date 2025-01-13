#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>

class MRIDataset {
public:
    int rows;
    int cols;
    int** data; // Dynamic 2D array to hold the MRI data

    MRIDataset(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
        }
    }

    ~MRIDataset() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void initializeData() {
        // Fill the dataset with sample data (e.g., pixel values)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = (i * cols + j + 1); // Example pixel values
            }
        }
    }

    void extractSlice(int startRow, int startCol, int sliceRows, int sliceCols, int** sliceData) {
        if (startRow < 0 || startCol < 0 || 
            startRow + sliceRows > rows || 
            startCol + sliceCols > cols) {
            throw std::out_of_range("Slice boundaries are out of range.");
        }

        for (int i = 0; i < sliceRows; ++i) {
            for (int j = 0; j < sliceCols; ++j) {
                sliceData[i][j] = data[startRow + i][startCol + j];
            }
        }
    }

    void modifySlice(int startRow, int startCol, int sliceRows, int sliceCols) {
        for (int i = 0; i < sliceRows; ++i) {
            for (int j = 0; j < sliceCols; ++j) {
                data[startRow + i][startCol + j] += 100; // Example modification
                if (data[startRow + i][startCol + j] > 255) { // Cap pixel value at 255
                    data[startRow + i][startCol + j] = 255;
                }
            }
        }
    }

    void printDataset() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << std::setw(3) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    const int numDatasets = 2; // Total number of MRI datasets
    const int rows = 5;         // Rows in each dataset
    const int cols = 5;         // Columns in each dataset

    // Creating an array of MRIDataset pointers
    MRIDataset* datasets[numDatasets];

    // Initialize each dataset
    for (int i = 0; i < numDatasets; ++i) {
        datasets[i] = new MRIDataset(rows, cols);
        datasets[i]->initializeData();
    }

    // Define the slice parameters
    int startRow = 1;
    int startCol = 1;
    int sliceRows = 3;
    int sliceCols = 3;

    // Allocate memory for the slice
    int** sliceData = new int*[sliceRows];
    for (int i = 0; i < sliceRows; ++i) {
        sliceData[i] = new int[sliceCols];
    }

    try {
        // Process each dataset
        for (int i = 0; i < numDatasets; ++i) {
            std::cout << "Original MRI Dataset " << (i + 1) << ":" << std::endl;
            datasets[i]->printDataset();

            // Extract the slice from the current dataset
            datasets[i]->extractSlice(startRow, startCol, sliceRows, sliceCols, sliceData);

            // Print the extracted slice
            std::cout << "\nExtracted Slice from Dataset " << (i + 1) << ":" << std::endl;
            for (int j = 0; j < sliceRows; ++j) {
                for (int k = 0; k < sliceCols; ++k) {
                    std::cout << std::setw(3) << sliceData[j][k] << " ";
                }
                std::cout << std::endl;
            }

            // Modify the central slice of the dataset
            std::cout << "\nModifying Slice in Dataset " << (i + 1) << "..." << std::endl;
            datasets[i]->modifySlice(startRow, startCol, sliceRows, sliceCols);

            // Print the modified dataset
            std::cout << "Modified MRI Dataset " << (i + 1) << ":" << std::endl;
            datasets[i]->printDataset();
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Clean up the allocated memory for slices
    for (int i = 0; i < sliceRows; ++i) {
        delete[] sliceData[i];
    }
    delete[] sliceData;

    // Clean up each dataset
    for (int i = 0; i < numDatasets; ++i) {
        delete datasets[i];
    }

    return 0;
}
