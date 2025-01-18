#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

class MemoryPool {
public:
    MemoryPool(size_t size);
    ~MemoryPool();
    
    void* allocate(size_t numBytes);
    void deallocate(void* ptr);
    
private:
    size_t poolSize;
    char* pool;
    std::vector<void*> freeBlocks;

    void registerFreeBlock(void* ptr, size_t size);
    void mergeFreeBlocks();
};

MemoryPool::MemoryPool(size_t size) 
    : poolSize(size), pool(static_cast<char*>(std::malloc(size)))
{
    assert(pool != nullptr);
}

MemoryPool::~MemoryPool() {
    std::free(pool);
}

void* MemoryPool::allocate(size_t numBytes) {
    if (numBytes <= 0 || numBytes > poolSize) {
        return nullptr;
    }

    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        size_t blockSize = *static_cast<size_t*>(*it - sizeof(size_t));
        if (blockSize >= numBytes) {
            freeBlocks.erase(it);
            return *it;
        }
    }

    return nullptr;  // No suitable free block found
}

void MemoryPool::deallocate(void* ptr) {
    if (ptr) {
        size_t blockSize = *static_cast<size_t*>(ptr - sizeof(size_t));
        registerFreeBlock(ptr, blockSize);
        mergeFreeBlocks();
    }
}

void MemoryPool::registerFreeBlock(void* ptr, size_t size) {
    *static_cast<size_t*>(ptr - sizeof(size_t)) = size;
    freeBlocks.push_back(static_cast<char*>(ptr) - sizeof(size_t)); // Account for size header
}

void MemoryPool::mergeFreeBlocks() {
    // For simplicity, merging logic is not implemented here.
}

// Helper function to calculate the size of a multi-dimensional array
size_t calculateArraySize(const std::vector<size_t>& dimensions, size_t elementSize) {
    size_t size = 1;
    for (const size_t& dim : dimensions) {
        size *= dim;
    }
    return size * elementSize;
}

// Example usage:
template <typename T>
T* allocateMultiDimensionalArray(MemoryPool& pool, const std::vector<size_t>& dimensions) {
    size_t elementSize = sizeof(T);
    size_t arraySize = calculateArraySize(dimensions, elementSize);
    void* ptr = pool.allocate(arraySize);
    
    if (ptr) {
        return static_cast<T*>(ptr);
    } else {
        std::cerr << "Memory allocation failed!" << std::endl;
        return nullptr;
    }
}

int main() {
    MemoryPool pool(1024 * 1024); // 1MB pool

    // Example 1: Allocate a 2D array of temperatures
    const size_t numDays = 30;
    const size_t numReadingsPerDay = 24;
    std::vector<size_t> dimensionsTemperature = {numDays, numReadingsPerDay};
    float* temperatures = allocateMultiDimensionalArray<float>(pool, dimensionsTemperature);

    if (temperatures) {
        // Populate the temperature array with dummy data
        for (size_t day = 0; day < numDays; ++day) {
            for (size_t reading = 0; reading < numReadingsPerDay; ++reading) {
                temperatures[day * numReadingsPerDay + reading] = 20.0f + (day % 10) + (reading % 2);
            }
        }

        // Example output: Print the first few readings
        for (size_t day = 0; day < 2; ++day) {
            for (size_t reading = 0; reading < 3; ++reading) {
                std::cout << "Temperature at day " << day + 1 << ", reading " << reading + 1 << ": "
                          << temperatures[day * numReadingsPerDay + reading] << std::endl;
            }
        }

        // Deallocate memory when done
        pool.deallocate(static_cast<void*>(temperatures));
    }

    // Example 2: Allocate a 3D array of pressure readings for different heights
    const size_t numHeights = 3;
    std::vector<size_t> dimensionsPressure = {numDays, numReadingsPerDay, numHeights};
    float* pressures = allocateMultiDimensionalArray<float>(pool, dimensionsPressure);

    if (pressures) {
        // Populate the pressure array with dummy data
        for (size_t day = 0; day < numDays; ++day) {
            for (size_t reading = 0; reading < numReadingsPerDay; ++reading) {
                for (size_t height = 0; height < numHeights; ++height) {
                    pressures[day * numReadingsPerDay * numHeights + reading * numHeights + height] = 
                        1013.0f + (day % 5) + (reading % 3) + (height * 1.0f);
                }
            }
        }

        // Example output: Print the first few readings at different heights
        for (size_t height = 0; height < numHeights; ++height) {
            std::cout << "\nPressure readings at height " << height + 1 << ":" << std::endl;
            for (size_t day = 0; day < 2; ++day) {
                for (size_t reading = 0; reading < 3; ++reading) {
                    std::cout << "  Day " << day + 1 << ", reading " << reading + 1 << ": "
                              << pressures[day * numReadingsPerDay * numHeights + reading * numHeights + height] << std::endl;
                }
            }
        }

        // Deallocate memory when done
        pool.deallocate(static_cast<void*>(pressures));
    }

    return 0;
}
