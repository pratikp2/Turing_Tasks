#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

template<typename T>
class MultiLayerArray3D {
public:
    // Constructor and other methods... (previous code)

    // Getter to return a shared pointer to a slice of the array (2D subset)
    std::shared_ptr<MultiLayerArray2D<T>> getSlice(size_t x) {
        if (x >= x_dim) {
            throw std::out_of_range("Index out of bounds");
        }

        class MultiLayerArray2D {
        public:
            MultiLayerArray2D(std::unique_ptr<std::unique_ptr<T[]>[]>&& slice) : slice(std::move(slice)) {}

            T& at(size_t y, size_t z) {
                if (y >= y_dim || z >= z_dim) {
                    throw std::out_of_range("Index out of bounds");
                }
                return slice[y][z];
            }

            const T& at(size_t y, size_t z) const {
                if (y >= y_dim || z >= z_dim) {
                    throw std::out_of_range("Index out of bounds");
                }
                return slice[y][z];
            }

            size_t y_dim, z_dim;
            std::unique_ptr<std::unique_ptr<T[]>[]> slice;
        };

        return std::make_shared<MultiLayerArray2D>(std::move(data[x]));
    }

    // Setter to modify an element at specific coordinates
    void setValue(size_t x, size_t y, size_t z, T value) {
        at(x, y, z) = value;
    }

private:
    // ... (previous code)
};

int main() {
    MultiLayerArray3D<int> array(2, 3, 4);

    // Initialising some values
    array.setValue(0, 1, 2, 5);
    array.setValue(1, 2, 3, 10);

    // Print initial dimensions and values
    auto [x, y, z] = array.dimensions();
    std::cout << "Initial dimensions: (" << x << ", " << y << ", " << z << ")\n";
    std::cout << "Value at (0, 1, 2): " << array.at(0, 1, 2) << std::endl;
    std::cout << "Value at (1, 2, 3): " << array.at(1, 2, 3) << std::endl;

    // Create a shared slice of the array at index 0
    std::shared_ptr<MultiLayerArray3D<int>::MultiLayerArray2D> slice = array.getSlice(0);

    // Modify values through the slice
    slice->at(1, 3) = 20;

    // Print modified value via slice
    std::cout << "\nModified value through slice: (0, 1, 3): " << slice->at(1, 3) << std::endl;

    return 0;
}
