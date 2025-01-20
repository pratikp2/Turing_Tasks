#include <iostream>
#include <algorithm>

template <typename T>
void applyTransformation(T* imageData, int width, int height, int channels, const std::function<T(T)>& transform) {
    for (int y = 0; y < height; ++y) {
        T* rowData = imageData + y * width * channels;
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                int index = (y * width + x) * channels + c;
                rowData[x * channels + c] = transform(rowData[x * channels + c]);
            }
        }
    }
}

int main() {
    // Sample image data for demonstration (width=3, height=2, channels=3)
    const int width = 3;
    const int height = 2;
    const int channels = 3;
    unsigned char imageData[] = {
        100, 150, 200, // Red, Green, Blue for pixel (0, 0)
        200, 100, 150, // Red, Green, Blue for pixel (1, 0)
        50, 100, 50,   // Red, Green, Blue for pixel (2, 0)
        255, 0, 0,     // Red, Green, Blue for pixel (0, 1)
        0, 255, 0,     // Red, Green, Blue for pixel (1, 1)
        0, 0, 255      // Red, Green, Blue for pixel (2, 1)
    };

    // Simple transformation to adjust brightness
    std::function<unsigned char(unsigned char)> adjustBrightness = [](unsigned char value) {
        // Adding 50 to each pixel value to adjust brightness
        const unsigned char maxValue = 255;
        unsigned char adjustedValue = std::min(value + 50, maxValue);
        return adjustedValue;
    };

    // Apply the transformation to the image data
    applyTransformation(imageData, width, height, channels, adjustBrightness);

    // Display the transformed image data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                int index = (y * width + x) * channels + c;
                std::cout << static_cast<int>(imageData[index]) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }

    return 0;
}
