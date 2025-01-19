#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// 3D array representation using smart pointers
template <typename T>
class MultiLayeredArray {
public:
    MultiLayeredArray(size_t depth, size_t width, size_t height)
        : depth_(depth), width_(width), height_(height) {
        // Initialize the layers using unique_ptr
        layers.resize(depth);
        for (size_t i = 0; i < depth; ++i) {
            layers[i] = make_unique<vector<vector<T>>>(width, vector<T>(height, 0));
        }
    }

    // Access elements using operator()
    T& operator()(size_t layer, size_t row, size_t col) {
        return (*layers[layer])[row][col];
    }

    const T& operator()(size_t layer, size_t row, size_t col) const {
        return (*layers[layer])[row][col];
    }

    // Get dimensions
    size_t getDepth() const { return depth_; }
    size_t getWidth() const { return width_; }
    size_t getHeight() const { return height_; }

private:
    size_t depth_, width_, height_;
    vector<unique_ptr<vector<vector<T>>>> layers;
};

// Example usage
int main() {
    const size_t depth = 3;
    const size_t width = 4;
    const size_t height = 5;

    // Create a 3D array of floats to store geographic data
    auto elevationData = make_unique<MultiLayeredArray<float>>(depth, width, height);

    // Populate the data with some example values
    for (size_t layer = 0; layer < depth; ++layer) {
        for (size_t row = 0; row < width; ++row) {
            for (size_t col = 0; col < height; ++col) {
                float value = (layer * 10.0f) + (row * 1.0f) + col;
                elevationData->operator()(layer, row, col) = value;
            }
        }
    }

    // Access and display some elements
    cout << "Element at (1, 2, 3): " << elevationData->operator()(1, 2, 3) << endl;

    return 0;
}
