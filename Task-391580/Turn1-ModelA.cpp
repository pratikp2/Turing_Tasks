#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include <cstring>
#include <cmath>

// Helper function to measure memory usage
size_t measureMemoryUsage() {
    #ifdef __linux__
        return malloc_usable_size(nullptr);
    #elseif _WIN32
        return _msize(nullptr);
    #else
        // Implement for other platforms if needed
        return 0;
    #endif
}

// Function to fill containers with data
template<typename Container>
void fillContainer(Container& container, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        container.push_back(i);
    }
}

int main() {
    const size_t numberOfElements = 100000;
    std::vector<int> vector;
    std::list<int> list;
    std::deque<int> deque;

    // Measure memory usage before filling containers
    std::cout << "Initial Memory Usage: " << measureMemoryUsage() << " bytes" << std::endl;

    // Fill containers with data
    std::cout << "Filling Vector..." << std::endl;
    fillContainer(vector, numberOfElements);
    std::cout << "Vector Filled." << std::endl;

    std::cout << "Filling List..." << std::endl;
    fillContainer(list, numberOfElements);
    std::cout << "List Filled." << std::endl;

    std::cout << "Filling Deque..." << std::endl;
    fillContainer(deque, numberOfElements);
    std::cout << "Deque Filled." << std::endl;

    // Measure memory usage after filling containers
    std::cout << "Memory Usage After Filling Vector: " << measureMemoryUsage() << " bytes" << std::endl;
    std::cout << "Memory Usage After Filling List: " << measureMemoryUsage() << " bytes" << std::endl;
    std::cout << "Memory Usage After Filling Deque: " << measureMemoryUsage() << " bytes" << std::endl;

    return 0;
}
