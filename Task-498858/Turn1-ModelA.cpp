#include <iostream>

class DynamicArray2D {
public:
    // Constructor: Allocating the 2D array
    DynamicArray2D(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        // Allocate memory for row pointers
        array = new int*[rows];
        // Allocate memory for each row
        for (int i = 0; i < rows; ++i) {
            array[i] = new int[cols];
        }
    }

    // Destructor: Deallocating the 2D array
    ~DynamicArray2D() {
        for (int i = 0; i < rows; ++i) {
            delete[] array[i]; // Free each row
        }
        delete[] array; // Free the array of row pointers
    }

    void setValue(int row, int col, int value) {
        if (row < rows && col < cols) {
            array[row][col] = value;
        }
    }

    int getValue(int row, int col) const {
        if (row < rows && col < cols) {
            return array[row][col];
        }
        return -1; // Handle out of bounds
    }

private:
    int** array;   // Pointer to pointer (2D array)
    int rows, cols; // Dimensions
};

int main() {
    DynamicArray2D array2D(3, 4); // Create a 3x4 dynamic array

    // Set values in the array
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            array2D.setValue(i, j, i * j); // Example values
        }
    }

    // Print values in the array
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << array2D.getValue(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
