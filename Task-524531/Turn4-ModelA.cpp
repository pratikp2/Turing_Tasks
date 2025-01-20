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

    T& operator()(int x, int y) {
        return data[y * width + x];
    }

    const T& operator()(int x, int y) const {
        return data[y * width + x];
    }
};

// Transformation function template
template<typename T>
void transformImage(const Image<T>& input, Image<T>& output, const std::vector<std::function<T(T)>>& transforms) {
    for (int y = 0; y < input.height; ++y) {
        for (int x = 0; x < input.width; ++x) {
            T pixelValue = input(x, y);
            // Apply all transformations in sequence
            for (const auto& transform : transforms) {
                pixelValue = transform(pixelValue);
            }
            output(x, y) = pixelValue;
        }
    }
}

// Example transformation: Adjusting brightness
template<typename T>
T adjustBrightness(T pixelValue, T adjustment) {
    return std::clamp(pixelValue + adjustment, static_cast<T>(0), static_cast<T>(255));
}

// Example transformation: Applying a threshold filter
template<typename T>
T applyThreshold(T pixelValue, T threshold) {
    return (pixelValue < threshold) ? static_cast<T>(0) : static_cast<T>(255);
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

    // Define brightness adjustment and threshold filter values
    int brightnessAdjustment = 30; // Increase brightness by 30
    int thresholdValue = 100;       // Set threshold at 100

    // Create transformation lambdas
    auto brightnessLambda = [brightnessAdjustment](int pixelValue) {
        return adjustBrightness(pixelValue, brightnessAdjustment);
    };

    auto thresholdLambda = [thresholdValue](int pixelValue) {
        return applyThreshold(pixelValue, thresholdValue);
    };

    // Store transformations in a vector
    std::vector<std::function<int(int)>> transformations = { brightnessLambda, thresholdLambda };

    // Apply the transformations
    transformImage(img, outputImg, transformations);

    // Print the transformed image
    std::cout << "Transformed Image (Brightness Adjustment and Threshold Filter):" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << outputImg(x, y) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
