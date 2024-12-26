#include <iostream>
#include <memory>
#include <vector>

class LazyArray {
public:
    LazyArray(size_t size) : size(size), arrayPointer(nullptr), isLoaded(false), version(0) {}

    // Add a function to increment the version when the original data changes
    void incrementVersion() { version++; }

    // ... (Other functions remain the same)

private:
    size_t size;
    int* arrayPointer;
    bool isLoaded;
    int version; // Added version for cache invalidation
};

class CachingManager {
public:
    void addArray(LazyArray* arr) { cachedArrays.push_back(arr); }
    void invalidateArray(LazyArray* arr) {
        for (auto& cachedArray : cachedArrays) {
            if (cachedArray == arr) {
                cachedArray->isLoaded = false; // Invalidate by unloading
                cachedArray->incrementVersion();
            }
        }
    }

private:
    std::vector<LazyArray*> cachedArrays;
};

int main() {
    size_t arraySize = 1000000;
    LazyArray myArray(arraySize);
    CachingManager cacheManager;
    cacheManager.addArray(&myArray);

    // ... (Usage continues)
    // Some other part of the code modifies the original data and calls
    cacheManager.invalidateArray(&myArray); // Invalidates the cache for this array

    return 0;
}
