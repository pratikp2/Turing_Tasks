#include <iostream>
#include <memory>
#include <vector>

class LazyArray {
public:
    LazyArray(size_t size) 
        : size(size), arrayPointer(nullptr), isLoaded(false), version(0) {}

    ~LazyArray() {
        if (arrayPointer) {
            delete[] arrayPointer;
        }
    }

    int& operator[](size_t index) {
        if (!isLoaded || isStale()) {
            loadFromDisk();
        }
        return arrayPointer[index];
    }

    void loadFromDisk() {
        std::cout << "Loading array from disk..." << std::endl;
        arrayPointer = new int[size];
        for (size_t i = 0; i < size; ++i) {
            arrayPointer[i] = i; // Fill with some test data
        }
        isLoaded = true;
        lastVersion = version; // Update the last version after loading
    }

    void modifyData(size_t index, int value) {
        // Simulate modifying the original data
        std::cout << "Modifying original data at index " << index << " to " << value << std::endl;
        version++; // Increment the version to indicate the data has changed
        // Here, you might also need to modify the original data source.
    }

    void invalidateCache() {
        std::cout << "Invalidating cache..." << std::endl;
        if (arrayPointer) {
            delete[] arrayPointer;
            arrayPointer = nullptr;
        }
        isLoaded = false;
    }

    bool isStale() {
        return version != lastVersion; // Compare current version with the last loaded version
    }

private:
    size_t size;
    int* arrayPointer;
    bool isLoaded; 
    unsigned int version;   // Current version of the data
    unsigned int lastVersion; // Version of the loaded data
};

int main() {
    size_t arraySize = 1000000; // 1 million elements
    LazyArray myArray(arraySize);

    // Access the array; this will load the data
    std::cout << myArray[999999] << std::endl; // Access last element

    // Modify the original data
    myArray.modifyData(0, 42); // Changes the version

    // Accessing again will invalidate the cache and reload
    std::cout << myArray[0] << std::endl; // Access first element, triggers reload

    return 0;
}
