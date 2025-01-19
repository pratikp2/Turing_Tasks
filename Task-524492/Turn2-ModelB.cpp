#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class SharedLayerArray2D {
public:
    SharedLayerArray2D(size_t x, size_t y) : x_dim(x), y_dim(y) {
        data = std::make_shared<std::vector<std::vector<T>>>(x, std::vector<T>(y));
    }

    T& at(size_t x, size_t y) {
        if (x >= x_dim || y >= y_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return (*data)[x][y];
    }

    const T& at(size_t x, size_t y) const {
        if (x >= x_dim || y >= y_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return (*data)[x][y];
    }

    std::tuple<size_t, size_t> dimensions() const {
        return std::make_tuple(x_dim, y_dim);
    }

private:
    size_t x_dim, y_dim;
    std::shared_ptr<std::vector<std::vector<T>>> data;
};

template<typename T>
class UniqueLayerArray2D {
public:
    UniqueLayerArray2D(size_t x, size_t y) : x_dim(x), y_dim(y) {
        data = std::make_unique<std::vector<std::vector<T>>>(x, std::vector<T>(y));
    }

    T& at(size_t x, size_t y) {
        if (x >= x_dim || y >= y_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return (*data)[x][y];
    }

    const T& at(size_t x, size_t y) const {
        if (x >= x_dim || y >= y_dim) {
            throw std::out_of_range("Index out of bounds");
        }
        return (*data)[x][y];
    }

    std::tuple<size_t, size_t> dimensions() const {
        return std::make_tuple(x_dim, y_dim);
    }

private:
    size_t x_dim, y_dim;
    std::unique_ptr<std::vector<std::vector<T>>> data;
};

int main() {
    {
        UniqueLayerArray2D<double> uniqueArray(2, 3);
        uniqueArray.at(0, 0) = 1.1;
        uniqueArray.at(1, 2) = 2.3;
        //uniqueArray.data.reset(); // Uncomment this to test what happens when the array is deleted
    }

    {
        SharedLayerArray2D<double> sharedArray(2, 3);
        sharedArray.at(0, 0) = 3.4;
        sharedArray.at(1, 1) = 4.5;
    }

    return 0;
}
