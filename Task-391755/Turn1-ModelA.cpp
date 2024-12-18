#include <iostream>
#include <vector>
#include <chrono>

void insertWithoutReserve(size_t numElements) {
    std::vector<int> vec;
    for (size_t i = 0; i < numElements; ++i) {
        vec.push_back(i);  // Resizing may occur here
    }
}

void insertWithReserve(size_t numElements) {
    std::vector<int> vec;
    vec.reserve(numElements);  // Reserve enough space upfront
    for (size_t i = 0; i < numElements; ++i) {
        vec.push_back(i);  // No resizing will occur now
    }
}

int main() {
    const size_t numElements = 1'000'000;  // Number of elements to insert

    // Measure insertion without reserve
    auto start = std::chrono::high_resolution_clock::now();
    insertWithoutReserve(numElements);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationWithoutReserve = end - start;
    std::cout << "Insertion without reserve took: " << durationWithoutReserve.count() << " seconds\n";

    // Measure insertion with reserve
    start = std::chrono::high_resolution_clock::now();
    insertWithReserve(numElements);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationWithReserve = end - start;
    std::cout << "Insertion with reserve took: " << durationWithReserve.count() << " seconds\n";

    return 0;
}
