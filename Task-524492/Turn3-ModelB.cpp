#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class MultiLayerArray3D {
public:
    MultiLayerArray3D(size_t x, size_t y, size_t z)
        : x_dim(x), y_dim(y), z_dim(z) {
        data = std::make_unique<std::vector<std::vector<std::vector<T>>>>>(x);
        for (size_t i = 0; i < x; ++i) {
            data[i] = std::vector<std::vector<T>>(y);
            for (size_t j = 0; j < y; ++j) {
                data[i][j] = std::vector<T>(z);
            }
        }
    }

    // Method to resize the array
    void resize(size_t x, size_t y, size_t z) {
        x_dim = x;
        y_dim = y;
        z_dim = z;

        data->resize(x);
        for (size_t i = 0; i < x; ++i) {
            data[i].resize(y);
            for (size_t j = 0; j < y; ++j) {
                data[i][j].resize(z);
            }
        }
    }

    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    const T& at(size_t x, size_t y, size_t z) const {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    std::tuple<size_t, size_t, size_t> dimensions() const {
        return std::make_tuple(x_dim, y_dim, z_dim);
    }

private:
    size_t x_dim, y_dim, z_dim;
    std::unique_ptr<std::vector<std::vector<std::vector<T>>>>> data;
};

int main() {
    MultiLayerArray3D<double> array(2, 2, 2);
    
    // Initializing some values
    array.at(0, 0, 0) = 1.0;
    array.at(1, 1, 1) = 10.0;

    std::cout << "Initial Dimensions: (" << array.dimensions().first << ", " << array.dimensions().second << ", " << array.dimensions().third << ")\n";
    std::cout << "Value at (0, 0, 0): " << array.at(0, 0, 0) << std::endl;
    std::cout << "Value at (1, 1, 1): " << array.at(1, 1, 1) << std::endl;

    // Resizing the array dynamically
    array.resize(4, 3, 2);

    std::cout << "\nResized Dimensions: (" << array.dimensions().first << ", " << array.dimensions().second << ", " << array.dimensions().third << ")\n";
    array.at(2, 1, 0) = 20.0;

    std::cout << "Value at (2, 1, 0): " << array.at(2, 1, 0) << std::endl;

    return 0;
}
