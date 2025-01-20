#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Image {
public:
    int width, height;
    T* data;

    Image(int w, int h) : width(w), height(h) {
        data = new T[w * h];
    }

    ~Image() {
        delete[] data;
    }

    T& operator()(int x, int y) {
        return data[y * width + x]; // Access pixel at (x, y)
    }
};

template<typename T>
void apply_filter(Image<T>& img, const std::vector<T>& filter, T* outputBuffer) {
    int filterSize = filter.size();
    int halfFilterSize = filterSize / 2;

    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            T pixelValue = 0;
            int filterIndex = 0;

            for (int f = -halfFilterSize; f <= halfFilterSize; ++f) {
                int px = std::clamp(x + f, 0, img.width - 1);
                pixelValue += img(px, y) * filter[filterIndex++];
            }

            outputBuffer[y * img.width + x] = pixelValue;
        }
    }
}

typedef void(*FilterFunction)(Image<int>&, const std::vector<int>&, int*);

template<typename T>
class FilterProcessor {
private:
    FilterFunction filterFunc;

public:
    explicit FilterProcessor(FilterFunction filter) : filterFunc(filter) {}

    void process(Image<T>& img, const std::vector<T>& filter) {
        T* outputBuffer = new T[img.width * img.height];
        filterFunc(img, filter, outputBuffer);

        // Copy back to the original image, or store this in a separate object if necessary
        std::copy(outputBuffer, outputBuffer + (img.width * img.height), img.data);
        
        delete[] outputBuffer;
    }
};

// Example usage
void applyGaussianFilter(Image<int>& img, const std::vector<int>& filter, int* outputBuffer) {
    apply_filter(img, filter, outputBuffer);
}

int main() {
    Image<int> img(800, 600);

    // Initialize image data...
    
    std::vector<int> gaussianFilter = { 1, 2, 1 };  // Example kernel for simplification
    FilterProcessor<int> processor(applyGaussianFilter);
    processor.process(img, gaussianFilter);

    return 0;
}
