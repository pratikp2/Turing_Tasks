#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <memory>
#include <functional>

template <typename T>
class PointerVector {
public:
    PointerVector(size_t initial_capacity = 10)
        : size_(0), capacity_(initial_capacity) {
        data_ = std::unique_ptr<T[]>(new T[capacity_]);
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            auto new_data = std::make_unique<T[]>(new_capacity);
            std::copy(data_.get(), data_.get() + size_, new_data.get());
            data_ = std::move(new_data);
            capacity_ = new_capacity;
        }
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_] = value;
        ++size_;
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    void bulk_modify(std::function<void(T&)> modifier) {
        for (size_t i = 0; i < size_; ++i) {
            modifier(at(i));
        }
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

private:
    void resize() {
        size_t new_capacity = capacity_ * 2;
        reserve(new_capacity);
    }

    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
};

// Benchmarking function
template <typename T>
void benchmark_vectors(size_t num_elements) {
    // Generate random data
    std::vector<T> stl_vector;
    PointerVector<T> custom_vector;

    // Pre-fill both vectors with data
    for (size_t i = 0; i < num_elements; ++i) {
        stl_vector.push_back(static_cast<T>(i));
        custom_vector.push_back(static_cast<T>(i));
    }

    // Benchmark random access
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; ++i) {
        volatile T temp = stl_vector[i]; // volatile to prevent optimization
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto stl_random_access_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; ++i) {
        volatile T temp = custom_vector.at(i); // volatile to prevent optimization
    }
    end = std::chrono::high_resolution_clock::now();
    auto custom_random_access_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Benchmark bulk modification
    start = std::chrono::high_resolution_clock::now();
    stl_vector[0] = 0; // Dummy operation for bulk modification
    std::for_each(stl_vector.begin(), stl_vector.end(), [](T& value) { value *= 2; });
    end = std::chrono::high_resolution_clock::now();
    auto stl_bulk_modify_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    custom_vector.bulk_modify([](T& value) { value *= 2; });
    end = std::chrono::high_resolution_clock::now();
    auto custom_bulk_modify_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Benchmark resizing
    start = std::chrono::high_resolution_clock::now();
    stl_vector.reserve(num_elements * 2); // Dummy resize
    end = std::chrono::high_resolution_clock::now();
    auto stl_resize_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    custom_vector.reserve(num_elements * 2); // Dummy resize
    end = std::chrono::high_resolution_clock::now();
    auto custom_resize_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Output the results
    std::cout << "Benchmark Results for " << num_elements << " elements:\n";
    std::cout << "STL Vector Random Access Time: " << stl_random_access_time << " µs\n";
    std::cout << "Custom Vector Random Access Time: " << custom_random_access_time << " µs\n";
    std::cout << "STL Vector Bulk Modify Time: " << stl_bulk_modify_time << " µs\n";
    std::cout << "Custom Vector Bulk Modify Time: " << custom_bulk_modify_time << " µs\n";
    std::cout << "STL Vector Resize Time: " << stl_resize_time << " µs\n";
    std::cout << "Custom Vector Resize Time: " << custom_resize_time << " µs\n";
    std::cout << "---------------------------------------------\n";
}

int main() {
    const std::vector<size_t> test_sizes = {1000, 10000, 100000, 1000000};

    for (size_t size : test_sizes) {
        benchmark_vectors<int>(size);
    }

    return 0;
}
