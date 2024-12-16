#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    const size_t n = 1'000'000;
    std::vector<int> data(n);

    // Generate random data
    for (size_t i = 0; i < n; ++i) {
        data[i] = rand();
    }

    {
        // Sequential execution
        auto seq_sum = std::reduce(data.begin(), data.end(), 0);
        std::cout << "Sequential sum: " << seq_sum << std::endl;
    }

    {
        // Parallel execution
        auto par_sum = std::reduce(std::execution::par, data.begin(), data.end(), 0);
        std::cout << "Parallel sum: " << par_sum << std::endl;
    }

    return 0;
}
