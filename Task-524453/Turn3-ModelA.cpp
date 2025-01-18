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

private:
    size_t poolSize;
    char* pool;
    std::vector<void*> freeBlocks;

    void registerFreeBlock(void* ptr, size_t size);
    void mergeFreeBlocks();
};

MemoryPool::MemoryPool(size_t size) 
    : poolSize(size), pool(static_cast<char*>(std::malloc(size))) {
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
    // Merging logic can be included here to enhance performance by defragmenting the pool.
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
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
