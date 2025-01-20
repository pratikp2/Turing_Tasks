#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include <stdexcept>

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

// Class to handle a sequence of transformations
template<typename T>
class TransformationSequence {
public:
    void addTransformation(std::function<T(T)> transformation) {
        transformations.push_back(transformation);
    }

    void apply(const Image<T>& input, Image<T>& output) const {
        Image<T> temp(input);
        const Image<T>* currentInput = &temp;

        for (const auto& transform : transformations) {
            for (int y = 0; y < currentInput->height; ++y) {
                for (int x = 0; x < currentInput->width; ++x) {
                    temp(x, y) = transform((*currentInput)(x, y));
                }
            }
            currentInput = &temp;
        }

        output = std::move(temp);
    }

private:
    std::vector<std::function<T(T)>> transformations;
};

// Transformation function templates
template<typename T, typename... F>
void transformImage(const Image<T>& input, Image<T>& output, F... transforms) {
    TransformationSequence<T> sequence;
    (sequence.addTransformation(transforms), ...);
    sequence.apply(input, output);
}

// Example transformations
template<typename T>
T adjustBrightness(T pixelValue, T adjustment) {
    return std::clamp(pixelValue + adjustment, static_cast<T>(0), static_cast<T>(255));
}

template<typename T>
T thresholdFilter(T pixelValue, T threshold) {
    return pixelValue > threshold ? static_cast<T>(255) : static_cast<T>(0);
}

int main() {
    const int width = 4;
    const int height = 4;

    // Create an image and fill it with some data
    Image<int> img(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            img(x, y) = (x + y) * 20;
        }
    }

    // Create an output image
    Image<int> outputImg(width, height);

    // Chaining transformations: Brightness adjustment and threshold filter
    int brightnessAdjustment = 30;
    int threshold = 100;

    transformImage<int>(img, outputImg,
                       [brightnessAdjustment](int pixelValue) { return adjustBrightness(pixelValue, brightnessAdjustment); },
                       [threshold](int pixelValue) { return thresholdFilter(pixelValue, threshold); });

    // Print the transformed image
    std::cout << "Transformed Image (Brightness + Threshold):" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << outputImg(x, y) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
