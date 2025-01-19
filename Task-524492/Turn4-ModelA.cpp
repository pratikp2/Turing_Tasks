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

    // Modifiable element access
    T& at(size_t x, size_t y, size_t z) {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    // Const accessor for read-only access
    const T& at(size_t x, size_t y, size_t z) const {
        if (x >= x_dim || y >= y_dim || z >= z_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y][z];
    }

    // Destructors and assignment operators are deleted/moved
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

// Example Function to use shared pointers
void sharedPointerExample() {
    // Using unique_ptr to manage the MultiLayerArray
    std::shared_ptr<MultiLayerArray3D<int>> sharedArray = std::make_shared<MultiLayerArray3D<int>>(2, 2, 2);
    
    // Directly accessing/modifying the data using shared pointer
    sharedArray->at(0, 0, 0) = 10;
    sharedArray->at(1, 1, 1) = 20;

    // Print modified values
    std::cout << "Value at (0, 0, 0): " << sharedArray->at(0, 0, 0) << std::endl;
    std::cout << "Value at (1, 1, 1): " << sharedArray->at(1, 1, 1) << std::endl;

    // Sharing and moving ownership
    std::shared_ptr<MultiLayerArray3D<int>> anotherSharedArray = sharedArray; // Share
    anotherSharedArray->at(0, 1, 0) = 30; // Modify via another shared pointer

    std::cout << "Value at (0, 1, 0) through another shared pointer: " 
              << anotherSharedArray->at(0, 1, 0) << std::endl;

    // Both sharedArray and anotherSharedArray will refer to the same data
}

int main() {
    // Creating a 3D array
    MultiLayerArray3D<int> array(2, 2, 2);

    // Initializing some values
    array.at(0, 0, 0) = 1;
    array.at(1, 1, 1) = 2;

    // Accessing and modifying elements
    std::cout << "Initial values:" << std::endl;
    std::cout << "Value at (0, 0, 0): " << array.at(0, 0, 0) << std::endl;
    std::cout << "Value at (1, 1, 1): " << array.at(1, 1, 1) << std::endl;

    // Resizing the array
    array.resize(3, 3, 3);

    std::cout << "Values after resizing:" << std::endl;
    std::cout << "Value at (0, 0, 0): " << array.at(0, 0, 0) << std::endl; // Should still be
    std::cout << "New value (default initialized) at (2, 2, 2): " << array.at(2, 2, 2) << std::endl;

    // Using shared pointers
    std::cout << "==========================" << std::endl;
    sharedPointerExample();

    return 0;
}
