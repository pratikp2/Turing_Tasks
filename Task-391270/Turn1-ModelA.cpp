#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "Original vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Using bidirectional iterators to reverse the vector
    std::vector<int>::iterator start = numbers.begin();
    std::vector<int>::iterator end = numbers.end();

    // Move the end iterator to the beginning
    while (start != end) {
        std::swap(*start, *end);
        ++start;
        --end;
    }

    std::cout << "Reversed vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
