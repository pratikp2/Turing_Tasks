#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

template<typename T>
class MultiLayerArray3D {
public:
    // Constructor to create a 3D array with given dimensions
    MultiLayerArray3D(size_t x, size_t y, size_t z)
        : x_dim(x), y_dim(y), z_dim(z) {
        allocateMemory();
    }

    // Copy constructor
    MultiLayerArray3D(const MultiLayerArray3D& other) {
        x_dim = other.x_dim;
        y_dim = other.y_dim;
        z_dim = other.z_dim;
        allocateMemory();
        copyData(other);
    }

    // Move constructor
    MultiLayerArray3D(MultiLayerArray3D&& other) noexcept
        : x_dim(other.x_dim), y_dim(other.y_dim), z_dim(other.z_dim), data(std::move(other.data)) {
        other.x_dim = 0;
        other.y_dim = 0;
        other.z_dim = 0;
    }

    // Resize array
    void resize(size_t new_x_dim, size_t new_y_dim, size_t new_z_dim) {
        // Create a new array with the new dimensions
        MultiLayerArray3D<T> new_array(new_x_dim, new_y_dim, new_z_dim);
        // Copy existing data into the new array
        for (size_t i = 0; i < std::min(x_dim, new_x_dim); ++i) {
            for (size_t j = 0; j < std::min(y_dim, new_y_dim); ++j) {
                for (size_t k = 0; k < std::min(z_dim, new_z_dim); ++k) {
                    new_array.at(i, j, k) = at(i, j, k);
                }
            }
        }

        // Swap new array with existing one to effectively change size
        std::swap(x_dim, new_array.x_dim);
        std::swap(y_dim, new_array.y_dim);
        std::swap(z_dim, new_array.z_dim);
        std::swap(data, new_array.data);
    }

    // Accessor to get a value at specific coordinates
    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    // Const accessor to get a value (const version)
    const T& at(size_t x, size_t y, size_t z) const {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    // Destructors and assignment operators are defaulted
    MultiLayerArray3D& operator=(const MultiLayerArray3D&) = delete; // Disable copy assignment
    MultiLayerArray3D& operator=(MultiLayerArray3D&&) noexcept = default; // Move assignment

    // Get dimensions
    std::tuple<size_t, size_t, size_t> dimensions() const {
        return std::make_tuple(x_dim, y_dim, z_dim);
    }

private:
    size_t x_dim, y_dim, z_dim; // Dimensions of the array
    std::unique_ptr<std::unique_ptr<std::unique_ptr<T[]>[]>[]> data; // 3D array data with unique pointers

    void allocateMemory() {
        data = std::make_unique<std::unique_ptr<std::unique_ptr<T[]>[]>[]>(x_dim);
        for (size_t i = 0; i < x_dim; ++i) {
            data[i] = std::make_unique<std::unique_ptr<T[]>[]>(y_dim);
            for (size_t j = 0; j < y_dim; ++j) {
                data[i][j] = std::make_unique<T[]>(z_dim);
            }
        }
    }

    void copyData(const MultiLayerArray3D& other) {
        for (size_t i = 0; i < other.x_dim; ++i) {
            for (size_t j = 0; j < other.y_dim; ++j) {
                for (size_t k = 0; k < other.z_dim; ++k) {
                    data[i][j][k] = other.data[i][j][k];
                }
            }
        }
    }
};

int main() {
    MultiLayerArray3D<int> array(2, 3, 4);

    // Setting some values
    array.at(0, 0, 0) = 1;
    array.at(0, 1, 2) = 5;

    // Print initial dimensions
    auto [x, y, z] = array.dimensions();
    std::cout << "Initial dimensions: (" << x << ", " << y << ", " << z << ")\n";

    // Resize to a larger dimension
    array.resize(3, 4, 5);

    // Print new dimensions
    std::tie(x, y, z) = array.dimensions();
    std::cout << "New dimensions after resizing: (" << x << ", " << y << ", " << z << ")\n";

    // Access some values (allowed values from old data will still be accessible)
    std::cout << "Value at (0, 1, 2): " << array.at(0, 1, 2) << std::endl;
    
    // Potentially access new elements (default initialized)
    std::cout << "New default value at (2, 3, 4): " << array.at(2, 3, 4) << std::endl; // Should show a default-initialized value.

    return 0;
}
