#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <stdexcept>

class MemoryPool {
public:
    MemoryPool(size_t size);
    ~MemoryPool();

    void* allocate(size_t numBytes);
    void deallocate(void* ptr);

    size_t totalAllocated() const { return totalAllocatedMemory; }
    size_t currentAllocated() const { return currentAllocatedMemory; }
    size_t peakAllocated() const { return peakAllocatedMemory; }

private:
    size_t poolSize;
    char* pool;
    std::vector<void*> freeBlocks;

    size_t totalAllocatedMemory = 0;
    size_t currentAllocatedMemory = 0;
    size_t peakAllocatedMemory = 0;

    void registerFreeBlock(void* ptr, size_t size);
    void mergeFreeBlocks();
};

MemoryPool::MemoryPool(size_t size)
    : poolSize(size), pool(static_cast<char*>(std::malloc(size))) {
    assert(pool != nullptr);

    // Initialize the freeBlocks vector with the entire pool as a single free block
    freeBlocks.push_back(pool);
}

MemoryPool::~MemoryPool() {
    std::free(pool);
}

void* MemoryPool::allocate(size_t numBytes) {
    if (numBytes <= 0 || numBytes > poolSize) {
        return nullptr;
    }

    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        char* block = static_cast<char*>(*it);
        size_t blockSize = poolSize - (block - pool); // Calculate remaining size in pool

        if (blockSize >= numBytes) {
            freeBlocks.erase(it); // Remove the block from the free list

            currentAllocatedMemory += numBytes;
            peakAllocatedMemory = std::max(peakAllocatedMemory, currentAllocatedMemory);
            totalAllocatedMemory += numBytes;

            // Return the pointer to the allocated block
            return static_cast<void*>(block);
        }
    }

    return nullptr;  // No suitable free block found
}

void MemoryPool::deallocate(void* ptr) {
    if (ptr) {
        size_t blockSize = poolSize - (static_cast<char*>(ptr) - pool); // Assume full size for simplicity
        registerFreeBlock(ptr, blockSize);
        mergeFreeBlocks();
        currentAllocatedMemory -= blockSize;
    }
}

void MemoryPool::registerFreeBlock(void* ptr, size_t size) {
    freeBlocks.push_back(ptr);
}

void MemoryPool::mergeFreeBlocks() {
    // Optional: Implement merging logic to reduce fragmentation
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
    MemoryPool& pool; // Reference to memory pool for this matrix
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, MemoryPool& pool) : rows(rows), cols(cols), pool(pool) {
    data = static_cast<T*>(pool.allocate(rows * cols * sizeof(T)));
    if (!data) {
        throw std::runtime_error("Memory allocation failed for matrix.");
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    pool.deallocate(static_cast<void*>(data)); // Deallocate the memory using the provided memory pool.
}

template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col) {
    assert(row < rows && col < cols && "Index out of bounds!");
    return data[row * cols + col]; // Access the element in a single-dimensional block
}

template <typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const {
    assert(row < rows && col < cols && "Index out of bounds!");
    return data[row * cols + col]; // Access the element in a single-dimensional block
}

// Example usage:
int main() {
    const size_t rows = 30; // 30 days
    const size_t cols = 24; // 24 readings per day (hourly)
    MemoryPool pool(100 * 1024); // 100 KB memory pool

    try {
        Matrix<float> temperatureMatrix(rows, cols, pool);

        // Populate the matrix with dummy temperature data
        for (size_t day = 0; day < rows; ++day) {
            for (size_t hour = 0; hour < cols; ++hour) {
                temperatureMatrix(day, hour) = static_cast<float>(day * 2 + hour); // Sample data
            }
        }

        // Print some values to demonstrate
        for (size_t day = 0; day < 3; ++day) { // Print first 3 days
            for (size_t hour = 0; hour < cols; ++hour) {
                std::cout << "Day " << day + 1 << " Hour " << hour << ": "
                          << temperatureMatrix(day, hour) << std::endl;
            }
        }

        // Log memory usage statistics
        std::cout << "Memory Usage Statistics:" << std::endl;
        std::cout << "  Total Allocated Memory: " << pool.totalAllocated() / 1024 << " KB" << std::endl;
        std::cout << "  Current Allocated Memory: " << pool.currentAllocated() / 1024 << " KB" << std::endl;
        std::cout << "  Peak Allocated Memory: " << pool.peakAllocated() / 1024 << " KB" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
