#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void measure_frequent_resizing(size_t target_size) {
    std::vector<int> v;
    auto start_time = std::clock();

    // Generate random elements and push_back to force resizing often
    for (size_t i = 0; i < target_size; ++i) {
        v.push_back(rand());
    }

    auto end_time = std::clock();
    double time_taken = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Frequent resizing (v.push_back()) for " << target_size 
              << " elements: " << time_taken << " seconds" << std::endl;
}

void measure_minimized_resizing(size_t target_size) {
    std::vector<int> v;
    
    // Reserve memory to minimize resizing
    v.reserve(target_size);
    
    auto start_time = std::clock();

    // Generate random elements and push_back without resizing
    for (size_t i = 0; i < target_size; ++i) {
        v.push_back(rand());
    }

    auto end_time = std::clock();
    double time_taken = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Minimized resizing (v.push_back() after v.reserve()) for " << target_size
              << " elements: " << time_taken << " seconds" << std::endl;
}
 
int main() {
    size_t target_size = 1000000;  // Let's test with a million elements
    srand(static_cast<unsigned>(std::time(0)));

    std::cout << "----------------- Perf Measurement -----------------" << std::endl;
    measure_frequent_resizing(target_size);
    measure_minimized_resizing(target_size);

    return 0;
}
