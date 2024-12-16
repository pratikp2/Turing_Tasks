#include <vector>
#include <algorithm>
#include <execution>
#include <iostream>
#include <chrono>

template<typename InputIt, typename OutputIt, typename UnaryOp>
OutputIt parallel_transform(InputIt first, InputIt last, OutputIt d_first, UnaryOp op) {
    auto length = std::distance(first, last);
    std::vector<std::future<void>> futures;

    int num_threads = std::thread::hardware_concurrency();
    int chunk_size = length / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        futures.emplace_back(std::async(std::launch::async, [=, &d_first] {
            auto start = first + i * chunk_size;
            auto end = (i == num_threads - 1) ? last : start + chunk_size;
            std::transform(start, end, d_first + (i * chunk_size), op);
        }));
    }

    for (auto &fut : futures) {
        fut.get();
    }

    return d_first + length;
}

int main() {
    const size_t N = 1000000;
    std::vector<int> v(N);
    std::vector<int> result(N);

    // Fill the vector with some values
    std::iota(v.begin(), v.end(), 0);

    auto start = std::chrono::high_resolution_clock::now();
    parallel_transform(v.begin(), v.end(), result.begin(), [](int x) { return x * 2; });
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time in seconds: " << elapsed.count() << "\n";
    return 0;
}
