#include <iostream>

const int ROWS = 5;
const int COLS = 4;

int main() {
    // Dynamic memory allocation for 2D array using pointers
    int** array2D = new int*[ROWS];

    for (int i = 0; i < ROWS; ++i) {
        array2D[i] = new int[COLS];
    }
    // Initializing the 2D array
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            array2D[i][j] = (i + 1) * (j + 1);
        }
    }
    // Displaying the 2D array
    std::cout << "2D Array using Pointers:\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << array2D[i][j] << " ";
        }
        std::cout << "\n";
    }
    // Deallocating the dynamically allocated memory
    for (int i = 0; i < ROWS; ++i) {
        delete[] array2D[i];
    }
    delete[] array2D;
    array2D = nullptr;

    return 0;
}
