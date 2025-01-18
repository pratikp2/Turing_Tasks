#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <string>

class MemoryPool {
public:
    MemoryPool(size_t size);
    ~MemoryPool();

    void* allocate(size_t numBytes);
    void deallocate(void* ptr);
    
    // New member functions for statistics
    size_t totalAllocated() const { return totalAllocatedBytes; }
    size_t peakUsage() const { return peakUsageBytes; }
    size_t allocationCount() const { return allocationCount; }
    size_t deallocationCount() const { return deallocationCount; }

    void logStatistics() const;

private:
    size_t poolSize;
    char* pool;
    std::vector<void*> freeBlocks;

    size_t totalAllocatedBytes = 0;
    size_t peakUsageBytes = 0;
    size_t allocationCount = 0;
    size_t deallocationCount = 0;

    void registerFreeBlock(void* ptr, size_t size);
    void mergeFreeBlocks();
};

MemoryPool::MemoryPool(size_t size)
    : poolSize(size), pool(static_cast<char*>(std::malloc(size))) {
    assert(pool != nullptr);
    freeBlocks.push_back(pool);
}

MemoryPool::~MemoryPool() {
    std::free(pool);
}

void* MemoryPool::allocate(size_t numBytes) {
    if (numBytes <= 0 || numBytes > poolSize) {
        return nullptr;
    }

    // Look for a free block
    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        char* block = static_cast<char*>(*it);
        size_t blockSize = poolSize - (block - pool);

        if (blockSize >= numBytes) {
            freeBlocks.erase(it); // Remove the block from the free list
            totalAllocatedBytes += numBytes;
            allocationCount++;

            // Update peak usage
            if (totalAllocatedBytes > peakUsageBytes) {
                peakUsageBytes = totalAllocatedBytes;
            }

            return static_cast<void*>(block);
        }
    }

    return nullptr;  // No suitable free block found
}

void MemoryPool::deallocate(void* ptr) {
    if (ptr) {
        size_t blockSize = poolSize - (static_cast<char*>(ptr) - pool);
        totalAllocatedBytes -= blockSize;
        deallocationCount++;

        registerFreeBlock(ptr, blockSize);
        mergeFreeBlocks();
    }
}

void MemoryPool::registerFreeBlock(void* ptr, size_t size) {
    freeBlocks.push_back(ptr);
}

void MemoryPool::mergeFreeBlocks() {
    // Optional: Implement merging logic to reduce fragmentation
}

void MemoryPool::logStatistics() const {
    std::cout << "Memory Pool Statistics:" << std::endl;
    std::cout << "Total Allocated Memory: " << totalAllocatedBytes << " bytes" << std::endl;
    std::cout << "Peak Memory Usage: " << peakUsageBytes << " bytes" << std::endl;
    std::cout << "Total Allocations: " << allocationCount << std::endl;
    std::cout << "Total Deallocations: " << deallocationCount << std::endl;
}

template <typename T>
class Matrix {
public:
    Matrix(size_t rows, size_t cols, MemoryPool& pool);
    ~Matrix();

    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    size_t numRows() const { return rows; }
    size_t numCols() const { return cols; }

private:
    size_t rows;
    size_t cols;
    T* data;
    MemoryPool& pool;
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, MemoryPool& pool)
    : rows(rows), cols(cols), pool(pool) {
    data = static_cast<T*>(pool.allocate(rows * cols * sizeof(T)));
    if (!data) {
        throw std::runtime_error("Memory allocation failed for matrix.");
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    pool.deallocate(static_cast<void*>(data));
}

template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col) {
    assert(row < rows && col < cols && "Index out of bounds!");
    return data[row * cols + col];
}

template <typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const {
    assert(row < rows && col < cols && "Index out of bounds!");
    return data[row * cols + col];
}

// Example usage
int main() {
    const size_t rows = 30; // 30 days
    const size_t cols = 24; // 24 readings per day (hourly)
    MemoryPool pool(100 * 1024); // 100 KB memory pool

    try {
        Matrix<float> temperatureMatrix(rows, cols, pool);

        // Populate the matrix with dummy temperature data
        for (size_t day = 0; day < rows; ++day) {
            for (size_t hour = 0; hour < cols; ++hour) {
                temperatureMatrix(day, hour) = static_cast<float>(day * 2 + hour);
            }
        }

        // Log memory statistics
        pool.logStatistics();
        
        // Print some values to demonstrate
        for (size_t day = 0; day < 3; ++day) { // Print first 3 days
            for (size_t hour = 0; hour < cols; ++hour) {
                std::cout << "Day " << day + 1 << " Hour " << hour << ": "
                          << temperatureMatrix(day, hour) << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
