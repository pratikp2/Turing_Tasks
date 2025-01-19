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
        // Create a 3D array using unique_ptr
        data = std::make_unique<std::unique_ptr<std::unique_ptr<T[]>[]>[]>(x);
        for (size_t i = 0; i < x; ++i) {
            data[i] = std::make_unique<std::unique_ptr<T[]>[]>(y);
            for (size_t j = 0; j < y; ++j) {
                data[i][j] = std::make_unique<T[]>(z);
            }
        }
    }

    // Accessor to get a value at specific coordinates
    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    // Const accessor to get a value at specific coordinates (const version)
    const T& at(size_t x, size_t y, size_t z) const {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    // Function to retrieve the dimensions of the array
    std::tuple<size_t, size_t, size_t> dimensions() const {
        return std::make_tuple(x_dim, y_dim, z_dim);
    }

private:
    size_t x_dim, y_dim, z_dim; // Dimensions of the array
    std::unique_ptr<std::unique_ptr<std::unique_ptr<T[]>[]>[]> data; // 3D array data with unique pointers
};

int main() {
    MultiLayerArray3D<int> array(4, 3, 2);
    
    // Setting some values
    array.at(0, 0, 0) = 1;
    array.at(0, 0, 1) = 2;
    array.at(1, 1, 0) = 3;

    // Retrieving values
    std::cout << "Value at (0, 0, 0): " << array.at(0, 0, 0) << std::endl;
    std::cout << "Value at (0, 0, 1): " << array.at(0, 0, 1) << std::endl;
    std::cout << "Value at (1, 1, 0): " << array.at(1, 1, 0) << std::endl;

    // Print dimensions
    auto [x, y, z] = array.dimensions();
    std::cout << "Dimensions: (" << x << ", " << y << ", " << z << ")\n";

    return 0;
}
