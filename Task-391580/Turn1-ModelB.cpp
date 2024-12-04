#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <iomanip>

template<typename Container>
void fillContainer(Container& container, size_t numElements) {
    for (size_t i = 0; i < numElements; ++i) {
        container.push_back(i);
    }
}

template<typename Container>
size_t memoryUsage(Container& container) {
    return sizeof(container) + container.size() * sizeof(typename Container::value_type);
}

void benchmarkMemoryUsage(size_t numElements) {
    std::vector<int> vec;
    std::list<int> lst;
    std::deque<int> deq;

    // Fill containers
    fillContainer(vec, numElements);
    fillContainer(lst, numElements);
    fillContainer(deq, numElements);

    // Output memory usage
    std::cout << "Memory Usage (in bytes):\n";
    std::cout << "Vector: " << memoryUsage(vec) << "\n";
    std::cout << "List: " << memoryUsage(lst) << "\n";
    std::cout << "Deque: " << memoryUsage(deq) << "\n";
}

int main() {
    size_t numElements = 10000;
    benchmarkMemoryUsage(numElements);
    return 0;
}
