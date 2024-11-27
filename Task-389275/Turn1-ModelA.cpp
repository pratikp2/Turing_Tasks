#include <iostream>
#include <vector>
#include <algorithm>

int sumArray(const std::vector<int>& arr) {
    return std::accumulate(arr.begin(), arr.end(), 0);
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Sum of array elements: " << sumArray(numbers) << std::endl;
    return 0;
}