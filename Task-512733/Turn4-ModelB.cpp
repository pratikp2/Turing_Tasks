#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

const int WIDTH = 1024;
const int HEIGHT = 1024;
const int NUM_THREADS = 4;  // Adjust the number of threads based on your CPU core count

std::mutex mtx;

void process_image(const std::vector<std::vector<int>>& image, int row_start, int row_end) {
    for (int i = row_start; i < row_end; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            auto start = std::chrono::high_resolution_clock::now();

            int value = image[i][j];
            // Example operation: inverting pixel value
            value = 255 - value;

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> duration = end - start;

            {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "Processing pixel (" << i << ", " << j << "): " << duration.count() << " microseconds.\n";
            }
        }
    }
}

int main() {
    // Create a large 2D vector representing an MRI image
    std::vector<std::vector<int>> image(HEIGHT, std::vector<int>(WIDTH, 0));

    // Fill the image with some values
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            image[i][j] = (i + j) % 256;
        }
    }

    // Calculate the row ranges for each thread
    int row_size = HEIGHT / NUM_THREADS + (HEIGHT % NUM_THREADS > 0 ? 1 : 0);

    std::thread threads[NUM_THREADS];

    // Launch threads with their respective row ranges
    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
        int row_start = thread_id * row_size;
        int row_end = std::min((thread_id + 1) * row_size, HEIGHT);
        threads[thread_id] = std::thread(process_image, image, row_start, row_end);
    }

    // Wait for all threads to complete
    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
        threads[thread_id].join();
    }

    return 0;
}
