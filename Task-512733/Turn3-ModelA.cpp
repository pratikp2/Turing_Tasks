#include <iostream>
#include <vector>
#include <chrono>

const int WIDTH = 1024;
const int HEIGHT = 1024;

// Function to simulate pixel-wise computation and measure time taken for each iteration
void process_image(const std::vector<std::vector<int>>& image) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            auto start = std::chrono::high_resolution_clock::now();

            // Simulate some processing on each pixel
            int value = image[i][j];
            // Example operation: inverting pixel value
            value = 255 - value;

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> duration = end - start;

            std::cout << "Processing pixel (" << i << ", " << j << "): " << duration.count() << " microseconds.\n";
        }
    }
}

int main() {
    // Create a large 2D vector representing an MRI image
    std::vector<std::vector<int>> image(HEIGHT, std::vector<int>(WIDTH, 0));

    // Fill the image with some values (for testing)
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            image[i][j] = (i + j) % 256; // Example pixel value
        }
    }

    // Process the image and measure time for each pixel processing
    process_image(image);

    return 0;
}
