#include <iostream>
#include <vector>
#include <list>
#include <ctime>

const int NUM_ELEMENTS = 1000000;

void measurePerformance() {
    std::cout << "Measuring performance with non-intrusive iterators:" << std::endl;
    std::vector<int> nonIntrusiveVector;
    clock_t start = clock();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        nonIntrusiveVector.push_back(i);
    }
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        nonIntrusiveVector.erase(nonIntrusiveVector.begin() + (NUM_ELEMENTS / 2));
    }
    clock_t end = clock();
    std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    std::cout << "Measuring performance with intrusive iterators:" << std::endl;
    std::list<int> intrusiveList;
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        intrusiveList.push_back(i);
    }
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        intrusiveList.erase(intrusiveList.begin());
    }
    end = clock();
    std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

int main() {
    measurePerformance();
    return 0;
}
