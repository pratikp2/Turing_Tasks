#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

// Image class to manage pixel data
template<typename T>
class Image {
public:
    int width, height;
    std::unique_ptr<T[]> data;

    Image(int w, int h) : width(w), height(h), data(new T[w * h]) {}

    // Access pixel at (x, y)
    T& operator()(int x, int y) {
        return data[y * width + x];
    }

    const T& operator()(int x, int y) const {
        return data[y * width + x];
    }
};

// Transformation function template
template<typename T, typename F>
void transformImage(const Image<T>& input, Image<T>& output, F transform) {
    for (int y = 0; y < input.height; ++y) {
        for (int x = 0; x < input.width; ++x) {
            output(x, y) = transform(input(x, y));
        }
    }
}

// Example transformation: Adjusting brightness
template<typename T>
T adjustBrightness(T pixelValue, T adjustment) {
    return std::clamp(pixelValue + adjustment, static_cast<T>(0), static_cast<T>(255));
}

int main() {
    const int width = 4;
    const int height = 4;

    // Create an image and fill it with some data
    Image<int> img(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            img(x, y) = (x + y) * 20; // Example pixel data
        }
    }

    // Create an output image
    Image<int> outputImg(width, height);

    // Define a brightness adjustment lambda
    int brightnessAdjustment = 30; // Increase brightness by 30
    auto brightnessLambda = [brightnessAdjustment](int pixelValue) {
        return adjustBrightness(pixelValue, brightnessAdjustment);
    };

    // Apply the transformation
    transformImage(img, outputImg, brightnessLambda);

    // Print the transformed image
    std::cout << "Transformed Image (Adjusted Brightness):" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << outputImg(x, y) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
