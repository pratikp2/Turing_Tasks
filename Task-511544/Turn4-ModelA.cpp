#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

const int N = 1000; // Number of elements to process
std::atomic<int> global_sum(0); // Atomic variable for sum

void add_to_sum(const std::vector<int>& data, int start, int end) {
    int local_sum = 0;
    
    for (int i = start; i < end; ++i) {
        local_sum += data[i]; // Local computation
    }
    
    global_sum += local_sum; // Atomically add to global_sum
}

int main() {
    std::vector<int> data(N, 1); // Populate array with 1s

    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    int chunk_size = N / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? N : (i + 1) * chunk_size;
        threads.emplace_back(add_to_sum, std::ref(data), start, end);
    }

    for (auto& t : threads) {
        t.join(); // Join threads
    }

    std::cout << "Total Sum: " << global_sum.load() << std::endl;

    return 0;
}
