#include <cstdlib> // For rand and RAND_MAX
#include <cstdio>  // For stderr and fprintf
#include <ctime>   // For seeding rand
#include <cassert>  // For assert

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256

// Assume the image is represented by a 1D array of grayscale values,
// where each element's value is between 0 and 255.
void adjustBrightness(unsigned char* imageData, unsigned int adjustment) {
    assert(imageData != nullptr);
    assert(adjustment >= 0 && adjustment <= 255);

    for (unsigned int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (unsigned int x = 0; x < IMAGE_WIDTH; ++x) {
            unsigned int index = y * IMAGE_WIDTH + x;
            unsigned char& pixelValue = imageData[index];

            // Apply brightness adjustment
            pixelValue = static_cast<unsigned char>(
                std::min(255u, std::max(0u, static_cast<int>(pixelValue) + adjustment))
            );
        }
    }
}

int main() {
    unsigned char* imageData = new unsigned char[IMAGE_WIDTH * IMAGE_HEIGHT];

    // Initialize image data with random grayscale values for demonstration
    srand(static_cast<unsigned>(time(0)));
    for (unsigned int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (unsigned int x = 0; x < IMAGE_WIDTH; ++x) {
            unsigned int index = y * IMAGE_WIDTH + x;
            imageData[index] = static_cast<unsigned char>(rand() % 256);
        }
    }

    // Example usage: Adjust brightness by 50
    adjustBrightness(imageData, 50);

    // Here, you could handle the saved image, but this example won't

    delete[] imageData;
    return 0;
}
