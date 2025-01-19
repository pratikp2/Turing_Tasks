#include <iostream>
#include <memory>
#include <chrono>
#include <stdexcept>
#include <tuple>
#include <cstdlib>

template<typename T>
class MultiLayerArray3D {
public:
    MultiLayerArray3D(size_t x, size_t y, size_t z) : x_dim(x), y_dim(y), z_dim(z) {
        allocateMemory();
    }

    ~MultiLayerArray3D() {
        releaseMemory();
    }

    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    void resize(size_t new_x_dim, size_t new_y_dim, size_t new_z_dim) {
        MultiLayerArray3D<T> new_array(new_x_dim, new_y_dim, new_z_dim);
        for (size_t i = 0; i < std::min(x_dim, new_x_dim); ++i) {
            for (size_t j = 0; j < std::min(y_dim, new_y_dim); ++j) {
                for (size_t k = 0; k < std::min(z_dim, new_z_dim); ++k) {
                    new_array.at(i, j, k) = at(i, j, k);
                }
            }
        }
        std::swap(x_dim, new_array.x_dim);
        std::swap(y_dim, new_array.y_dim);
        std::swap(z_dim, new_array.z_dim);
        std::swap(data, new_array.data);
    }

private:
    size_t x_dim, y_dim, z_dim;
    std::unique_ptr<std::unique_ptr<std::unique_ptr<T[]>[]>[]> data;

    void allocateMemory() {
        data = std::make_unique<std::unique_ptr<std::unique_ptr<T[]>[]>[]>(x_dim);
        for (size_t i = 0; i < x_dim; ++i) {
            data[i] = std::make_unique<std::unique_ptr<T[]>[]>(y_dim);
            for (size_t j = 0; j < y_dim; ++j) {
                data[i][j] = std::make_unique<T[]>(z_dim);
            }
        }
    }

    void releaseMemory() {
        // Nothing needed because unique_ptr handles it automatically
    }
};

// Version using Raw Pointers
template<typename T>
class RawPointerMultiLayerArray3D {
public:
    RawPointerMultiLayerArray3D(size_t x, size_t y, size_t z)
        : x_dim(x), y_dim(y), z_dim(z), data(nullptr) {
        allocateMemory();
    }

    ~RawPointerMultiLayerArray3D() {
        releaseMemory();
    }

    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    void resize(size_t new_x_dim, size_t new_y_dim, size_t new_z_dim) {
        T*** new_data = new T**[new_x_dim];
        for (size_t i = 0; i < new_x_dim; ++i) {
            new_data[i] = new T*[new_y_dim];
            for (size_t j = 0; j < new_y_dim; ++j) {
                new_data[i][j] = new T[new_z_dim]{};
            }
        }

        // Copy old data to new location
        for (size_t i = 0; i < std::min(x_dim, new_x_dim); ++i) {
            for (size_t j = 0; j < std::min(y_dim, new_y_dim); ++j) {
                for (size_t k = 0; k < std::min(z_dim, new_z_dim); ++k) {
                    new_data[i][j][k] = at(i, j, k);
                }
            }
        }

        releaseMemory();

        // Update dimensions and data
        x_dim = new_x_dim;
        y_dim = new_y_dim;
        z_dim = new_z_dim;
        data = new_data;
    }

private:
    size_t x_dim, y_dim, z_dim;
    T*** data;

    void allocateMemory() {
        data = new T**[x_dim];
        for (size_t i = 0; i < x_dim; ++i) {
            data[i] = new T*[y_dim];
            for (size_t j = 0; j < y_dim; ++j) {
                data[i][j] = new T[z_dim]{};
            }
        }
    }

    void releaseMemory() {
        if (data) {
            for (size_t i = 0; i < x_dim; ++i) {
                for (size_t j = 0; j < y_dim; ++j) {
                    delete[] data[i][j];
                }
                delete[] data[i];
            }
            delete[] data;
        }
        data = nullptr;
    }
};

template<typename DataType>
void benchmarkSmartPointer(size_t x, size_t y, size_t z) {
    auto start = std::chrono::high_resolution_clock::now();
    MultiLayerArray3D<DataType> smartArray(x, y, z);
    
    // Fill the array with values
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            for (size_t k = 0; k < z; ++k) {
                smartArray.at(i, j, k) = i + j + k; // Sample operation
            }
        }
    }
    
    // Resize the array
    smartArray.resize(x + 1, y + 1, z + 1);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Smart Pointer Version: Execution Time: " << duration.count() << " seconds" << std::endl;
}

template<typename DataType>
void benchmarkRawPointer(size_t x, size_t y, size_t z) {
    auto start = std::chrono::high_resolution_clock::now();
    RawPointerMultiLayerArray3D<DataType> rawArray(x, y, z);
    
    // Fill the array with values
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            for (size_t k = 0; k < z; ++k) {
                rawArray.at(i, j, k) = i + j + k; // Sample operation
            }
        }
    }
    
    // Resize the array
    rawArray.resize(x + 1, y + 1, z + 1);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Raw Pointer Version: Execution Time: " << duration.count() << " seconds" << std::endl;
}

int main() {
    const size_t x = 100;
    const size_t y = 100;
    const size_t z = 100;

    std::cout << "Benchmarking MultiLayerArray3D" << std::endl;
    benchmarkSmartPointer<int>(x, y, z);
    benchmarkRawPointer<int>(x, y, z);

    return 0;
}
