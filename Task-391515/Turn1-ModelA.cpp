#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>

template <typename T>
T find_max(const T& container) {
    if (container.empty()) {
        throw std::runtime_error("Container is empty");
    }

    return *std::max_element(std::begin(container), std::end(container));
}

int main() {
    std::vector<int> intVec = {1, 5, 2, 3, 4};
    std::array<double, 5> doubleArr = {3.5, 2.2, 5.1, 1.4, 4.0};

    try {
        std::cout << "Max in int vector: " << find_max(intVec) << std::endl;
        std::cout << "Max in double array: " << find_max(doubleArr) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
