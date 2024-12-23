#include <iostream>
#include <vector>
#include <thread>

void process_chunk(std::vector<int>& data, std::vector<int>& results, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        results[i] = process(data[i]); // Independent process function
    }
}

int main() {
    std::vector<int> data(1'000'000);  // Example data
    std::vector<int> results(data.size());

    std::vector<std::thread> threads;
    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = data.size() / num_threads;

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? data.size() : start + chunk_size;
        threads.emplace_back(process_chunk, std::ref(data), std::ref(results), start, end);
    }

    for (auto& t : threads) {
        t.join();  // Wait for all threads to finish
    }
    return 0;
}
