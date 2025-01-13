#include <iostream>
#include <vector>
#include <chrono>

const int WIDTH = 1024;
const int HEIGHT = 1024;

void process_image(const std::vector<std::vector<int>>& image) {
    for (int i = 0; i < HEIGHT; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int j = 0; j < WIDTH; ++j) {
            int value = image[i][j];
            value = 255 - value;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Iteration " << i << " took: " << duration.count() << " seconds." << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> image(HEIGHT, std::vector<int>(WIDTH, 0));

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            image[i][j] = (i + j) % 256;
        }
    }

    process_image(image);

    return 0;
}
