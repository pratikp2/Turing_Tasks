#include <iostream>
#include <memory>
#include <vector>

class LazyArray {
public:
    LazyArray(size_t size) : size(size), arrayPointer(nullptr), isLoaded(false) {}
    
    ~LazyArray() {
        if (arrayPointer) {
            delete[] arrayPointer;
        }
    }

    // Function to access elements
    int& operator[](size_t index) {
        if (!isLoaded) {
            loadFromDisk();
        }
        return arrayPointer[index];
    }

    // Simulating loading from a source (e.g., file, database)
    void loadFromDisk() {
        std::cout << "Loading array from disk..." << std::endl;
        // Here, we're simulating a disk load
        arrayPointer = new int[size];
        for (size_t i = 0; i < size; ++i) {
            arrayPointer[i] = i; // Fill with some test data
        }
        isLoaded = true;
    }

    // If you do not want to load initially
    void unload() {
        if (arrayPointer) {
            delete[] arrayPointer;
            arrayPointer = nullptr;
            isLoaded = false;
            std::cout << "Array unloaded from memory." << std::endl;
        }
    }

private:
    size_t size;
    int* arrayPointer;
    bool isLoaded; // Flag to check if array is loaded
};

int main() {
    size_t arraySize = 1000000; // 1 million elements
    LazyArray myArray(arraySize);

    // Sample usage; only loads the array when first accessed
    std::cout << myArray[999999] << std::endl; // Access last element

    // Example of unloading
    myArray.unload();

    // Further access will reload
    std::cout << myArray[0] << std::endl; // Access first element again

    return 0;
}
