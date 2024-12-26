#include <iostream>
#include <cstdlib> // For malloc and free
#include <cstddef> // For size_t

template <typename T>
class MemoryPool {
public:
    MemoryPool(size_t num_elements, size_t element_size)
        : num_elements_(num_elements), element_size_(element_size) {
        // Calculate the total size of the memory pool
        size_t pool_size = num_elements_ * element_size_;

        // Allocate memory for the pool using malloc
        raw_memory_ = malloc(pool_size);

        if (raw_memory_ == nullptr) {
            std::cerr << "Error: Memory allocation failed.\n";
            std::exit(EXIT_FAILURE);
        }

        // Initialize the free list
        free_list_ = static_cast<T**>(raw_memory_);
        for (size_t i = 1; i < num_elements_; ++i) {
            free_list_[i] = reinterpret_cast<T*>(static_cast<char*>(free_list_) + i * element_size_);
        }
        free_list_[num_elements_] = nullptr;
    }

    ~MemoryPool() {
        // Free the memory pool using free
        free(raw_memory_);
    }

    T* allocate() {
        if (free_list_ == nullptr) {
            std::cerr << "Error: Memory pool is empty.\n";
            std::exit(EXIT_FAILURE);
        }
        T* result = free_list_;
        free_list_ = free_list_[1];
        return result;
    }

    void deallocate(T* ptr) {
        ptr[1] = free_list_;
        free_list_ = ptr;
    }

private:
    size_t num_elements_;
    size_t element_size_;
    void* raw_memory_;
    T** free_list_;
};

class DataPoint {
public:
    DataPoint() = default;
    // Add your data members here
    float x;
    float y;
};

int main() {
    const size_t num_data_points = 1000;
    const size_t data_point_size = sizeof(DataPoint);

    MemoryPool<DataPoint> data_point_pool(num_data_points, data_point_size);

    // Allocate memory from the pool
    for (int i = 0; i < num_data_points; ++i) {
        DataPoint* data_point = data_point_pool.allocate();
        data_point->x = static_cast<float>(i);
        data_point->y = static_cast<float>(i * i);
        // Process the data point
        // ...
    }

    // Deallocate memory back to the pool (you may not need this in all cases, especially in real-time apps)
    for (int i = num_data_points - 1; i >= 0; --i) {
        DataPoint* data_point = static_cast<DataPoint*>(static_cast<char*>(data_point_pool.raw_memory_) + i * data_point_size);
        data_point_pool.deallocate(data_point);
    }

    return 0;
}
