#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

const int WIDTH = 1024;
const int HEIGHT = 1024;

// Function to simulate pixel-wise computation
void process_image_section(const std::vector<std::vector<int>>& image, int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            auto start = std::chrono::high_resolution_clock::now();

            // Simulate some processing on each pixel
            int value = image[i][j];
            value = 255 - value; // Example operation: inverting pixel value

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> duration = end - start;

            std::cout << "Processing pixel (" << i << ", " << j << "): " << duration.count() << " microseconds.\n";
        }
    }
}

void process_image(const std::vector<std::vector<int>>& image) {
    const int num_threads = std::thread::hardware_concurrency(); // Get number of threads supported by the hardware
    std::vector<std::thread> threads;
    int rows_per_thread = HEIGHT / num_threads;

    // Create threads to process image sections
    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * rows_per_thread;
        int end_row = (t == num_threads - 1) ? HEIGHT : start_row + rows_per_thread; // Handle last thread for odd number of rows
        threads.emplace_back(process_image_section, std::ref(image), start_row, end_row);
    }

    // Join all threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
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

    // Process the image and measure time
    auto start = std::chrono::high_resolution_clock::now();
    process_image(image);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Total processing time (multithreaded): " << duration.count() << " seconds." << std::endl;

    return 0;
}
