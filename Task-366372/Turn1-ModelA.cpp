#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>

// Allocate a specific amount of memory
void allocate_memory(size_t size) {
    size_t buffer_size = 1024 * 1024; // 1MB
    char* buffer = static_cast<char*>(malloc(buffer_size));
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = i % 256;
    }
    free(buffer);
}

int main() {
    const size_t num_allocations = 100000;
    const size_t thread_count = 4;
    std::vector<std::thread> threads;

    // Start time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Create and start threads
    for (size_t i = 0; i < thread_count; ++i) {
        threads.emplace_back([=] {
            for (size_t j = 0; j < num_allocations; ++j) {
                allocate_memory(100); // Allocate 100 bytes each time
            }
        });
    }

    // Join threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // End time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate total duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Output the result
    std::cout << "Total memory allocations: " << num_allocations * thread_count << std::endl;
    std::cout << "Total time taken: " << duration.count() << " microseconds" << std::endl;

    return 0;
}