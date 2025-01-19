#include <iostream>
#include <memory>
#include <chrono>
#include <stdexcept>
#include <vector>


template<typename T>
class MultiLayerArray3DRaw {
public:
    MultiLayerArray3DRaw(size_t x, size_t y, size_t z)
        : x_dim(x), y_dim(y), z_dim(z) {
        allocateMemory();
    }

    ~MultiLayerArray3DRaw() {
        freeMemory();
    }

    // Resize array and modify contents
    void resizeAndUpdate(size_t new_x_dim, size_t new_y_dim, size_t new_z_dim) {
        freeMemory();
        allocateMemory(new_x_dim, new_y_dim, new_z_dim);

        // Copy existing data to new dimensions
        for (size_t i = 0; i < std::min(x_dim, new_x_dim); ++i) {
            for (size_t j = 0; j < std::min(y_dim, new_y_dim); ++j) {
                for (size_t k = 0; k < std::min(z_dim, new_z_dim); ++k) {
                    data[new_x_dim * new_y_dim * i + new_y_dim * j + k] = data[x_dim * y_dim * i + y_dim * j + k];
                }
            }
        }
        x_dim = new_x_dim;
        y_dim = new_y_dim;
        z_dim = new_z_dim;
    }

    // Access element
    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x_dim * y_dim * x + y_dim * y + z];
    }

    // Const accessor for read-only access
    const T& at(size_t x, size_t y, size_t z) const {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x_dim * y_dim * x + y_dim * y + z];
    }

private:
    size_t x_dim, y_dim, z_dim; // Dimensions of the array
    T* data;

    void allocateMemory() {
        data = new T[x_dim * y_dim * z_dim];
    }

    void allocateMemory(size_t new_x_dim, size_t new_y_dim, size_t new_z_dim) {
        data = new T[new_x_dim * new_y_dim * new_z_dim];
    }

    void freeMemory() {
        if (data) {
            delete[] data;
            data = nullptr;
        }
    }
};


void benchmarkPerformance(const std::string& type) {
    auto start = std::chrono::high_resolution_clock::now();

    // Timing element access and resize for MultiLayerArray
    MultiLayerArray3D<int> array(500, 400, 300);
    array.at(100, 200, 100) = 1;
    array.resize(700, 600, 500);

    const auto end = std::chrono::high_resolution_clock::now();
    const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    const double timeInSeconds = static_cast<double>(nanoseconds.count()) * 1e-9;

    std::cout << "---[" << type << "] benchmarking---" << std::endl;
    std::cout << "Elapsed time: " << timeInSeconds << " seconds" << std::endl;
}

int main() {
    benchmarkPerformance("Smart Pointers");

    return 0;
}
