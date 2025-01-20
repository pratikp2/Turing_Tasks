#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

// Image class to manage pixel data
template<typename T>
class Image {
public:
    int width, height;
    std::unique_ptr<T[]> data;

    Image(int w, int h) : width(w), height(h), data(new T[w * h]) {}

    T& operator()(int x, int y) {
        return data[y * width + x]; // Access pixel at (x, y)
    }
};

// Base class for Filters
template<typename T>
class Filter {
public:
    virtual void apply(const Image<T>& input, Image<T>& output) = 0;
    virtual ~Filter() = default;
};

// Example: Gaussian Filter
template<typename T>
class GaussianFilter : public Filter<T> {
    std::vector<T> kernel;

public:
    GaussianFilter(const std::vector<T>& k) : kernel(k) {}

    void apply(const Image<T>& input, Image<T>& output) override {
        int filterSize = kernel.size();
        int halfFilterSize = filterSize / 2;

        for (int y = 0; y < input.height; ++y) {
            for (int x = 0; x < input.width; ++x) {
                T pixelValue = 0;
                int filterIndex = 0;

                for (int f = -halfFilterSize; f <= halfFilterSize; ++f) {
                    int px = std::clamp(x + f, 0, input.width - 1);
                    pixelValue += input(px, y) * kernel[filterIndex++];
                }

                output(x, y) = pixelValue;
            }
        }
    }
};

// Chainable filter processor
template<typename T>
class FilterProcessor {
    std::vector<std::unique_ptr<Filter<T>>> filters;

public:
    void addFilter(std::unique_ptr<Filter<T>> filter) {
        filters.push_back(std::move(filter));
    }

    void process(const Image<T>& input, Image<T>& output) {
        Image<T> temp(input.width, input.height);
        const Image<T>* currentInput = &input;

        for (const auto& filter : filters) {
            filter->apply(*currentInput, temp);
            currentInput = &temp; // Use the output of the current filter as input for the next
        }

        // Final output is now in temp
        output = temp; // Copy final result to output
    }
};

// Example main function to demonstrate usage
int main() {
    const int width = 800;
    const int height = 600;

    // Create an image and fill it with some data
    Image<int> img(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            img(x, y) = (x + y) % 256; // Example pixel data
        }
    }

    // Create a FilterProcessor and add filters
    FilterProcessor<int> processor;
    std::vector<int> gaussianKernel = { 1, 2, 1 }; // Simple kernel for Gaussian filter
    processor.addFilter(std::make_unique<GaussianFilter<int>>(gaussianKernel));

    // Create output image
    Image<int> outputImg(width, height);

    // Process the image
    processor.process(img, outputImg);

    // Example output (printing the first few pixels)
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            std::cout << outputImg(x, y) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
