#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

int main() {
    const int size = 1'000'000;
    std::vector<int> data(size);

    // Generate random data for sorting
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1'000'000);
    for (auto& i : data) {
        i = dis(gen);
    }

    // Measure the sorting time using std::chrono
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(data.begin(), data.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Sorting time: " << duration.count() << " microseconds\n";
    }

    return 0;
}
