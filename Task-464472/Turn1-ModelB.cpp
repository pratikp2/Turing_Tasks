#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>

const int NUM_THREADS = 4;

unsigned long long concurrentBitwiseANDSum(const std::vector<int>& array) {
    size_t n = array.size();

    // Calculate the chunk size for each thread
    size_t chunk_size = n / NUM_THREADS + (n % NUM_THREADS > 0);

    std::atomic<unsigned long long> partial_sums[NUM_THREADS]{0};

    // Start threads to calculate partial sums concurrently
    std::thread threads[NUM_THREADS];
    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
        size_t start = thread_id * chunk_size;
        size_t end = std::min((thread_id + 1) * chunk_size, n);
        
        threads[thread_id] = std::thread([thread_id, start, end, &array, &partial_sums] {
            unsigned long long partial_sum = 0;
            for (size_t i = start; i < end; ++i) {
                for (size_t j = i + 1; j < n; ++j) {
                    partial_sum += static_cast<unsigned long long>(array[i] & array[j]);
                }
            }
            partial_sums[thread_id] = partial_sum;
        });
    }

    // Join all threads
    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
        threads[thread_id].join();
    }
    
    // Calculate the final sum of partial sums
    unsigned long long total_sum = 0;
    for (auto partial_sum : partial_sums) {
        total_sum += partial_sum;
    }

    return total_sum;
}

int main() {
    std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unsigned long long sum = concurrentBitwiseANDSum(array);
    std::cout << "Sum of bitwise AND of all pairs: " << sum << std::endl;

    return 0;
}
