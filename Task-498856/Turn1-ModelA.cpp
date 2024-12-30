#include <iostream>
#include <stdexcept>

class ArraySlicer {
public:
    ArraySlicer(int size) : size(size) {
        arr = new int[size];  // Dynamic array allocation
    }

    ~ArraySlicer() {
        delete[] arr;  // Clean up memory
    }

    // Populate the array
    void populateArray() {
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;  // Fill with values from 1 to size
        }
    }

    // Slice the array using pointer arithmetic
    void sliceArray(int start, int length) const {
        if (start < 0 || start + length > size) {
            throw std::out_of_range("Slice parameters are out of bounds.");
        }

        // Pointer to the starting location of the slice
        const int* slice_start = arr + start;

        std::cout << "Sliced array: ";
        
        // Iterate over the sliced portion using a pointer
        for (const int* p = slice_start; p < slice_start + length; ++p) {
            std::cout << *p << " ";
        }
        
        std::cout << std::endl;
    }

private:
    int* arr;  // Dynamic array
    int size;  // Size of the array
};

int main() {
    try {
        ArraySlicer slicer(10);  // Create an array of size 10
        slicer.populateArray();    // Populate the array
        
        // Slice the array: starting from index 3, of length 5
        slicer.sliceArray(3, 5);   // Output: Sliced array: 4 5 6 7 8
        
        // Attempting an out-of-bounds slice will throw an exception
        // slicer.sliceArray(8, 5);   // Uncommenting this will throw an error

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
