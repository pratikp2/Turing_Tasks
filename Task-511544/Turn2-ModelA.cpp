#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

const int N = 1000; // Size of the matrix
std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 1));
std::mutex mtx; // Mutex for synchronization
int global_counter = 0; // Shared resource

void compute(int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            std::this_thread::sleep_for(std::chrono::microseconds(1)); // Simulate work
            matrix[i][j] += 1; // Modify the matrix (write operation)
            
            // Use mutex to safely increment a shared counter
            {
                std::lock_guard<std::mutex> lock(mtx);
                global_counter++; // Increment the global counter
            }
        }
    }
}

int main() {
    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int rows_per_thread = N / num_threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? N : start_row + rows_per_thread;
        threads.emplace_back(compute, start_row, end_row);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Global counter: " << global_counter << std::endl; 
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
