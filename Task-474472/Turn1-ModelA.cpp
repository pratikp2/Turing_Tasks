#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

int main() {
    // Create a large vector of random integers
    std::vector<int> numbers(100000);
    std::generate(numbers.begin(), numbers.end(), std::rand);

    // Measure execution time of sorting with std::chrono
    auto start = std::chrono::high_resolution_clock::now();

    // Sort the numbers using std::sort (which is highly optimized)
    std::sort(numbers.begin(), numbers.end());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output elapsed time
    std::cout << "Sorting took " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
