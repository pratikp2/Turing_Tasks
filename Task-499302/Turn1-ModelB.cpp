#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding rand()

void factorial(int n, int depth) {
    if (n == 0 || n == 1) {
        std::cout << "Base Case: " << n << "! = 1 (Depth: " << depth << ")\n";
        return;
    }

    std::cout << "Recursive Call: " << n << "! (Depth: " << depth << ")\n";
    factorial(n - 1, depth + 1);
    std::cout << "Result: " << n << " * " << (n - 1) << "! = " << n << " * ";
}

int mergeSortHelper(std::vector<int>& array, int low, int high, int depth) {
    if (low < high) {
        std::cout << "\n--- Depth " << depth << " ---\n";
        int mid = (low + high) / 2;
        mergeSortHelper(array, low, mid, depth+1);
        mergeSortHelper(array, mid + 1, high, depth+1);
        merge(array, low, mid, high);
    }
    return 0;
}

void merge(std::vector<int>& array, int low, int mid, int high) {
    std::cout << "Merging [" << low << ", " << mid << "] and [" << mid + 1 << ", " << high << "]\n";
    std::vector<int> left, right;
    for (int i = low; i <= mid; ++i) {
        left.push_back(array[i]);
    }
    for (int i = mid + 1; i <= high; ++i) {
        right.push_back(array[i]);
    }

    int left_index = 0, right_index = 0, original_index = low;

    while (left_index < left.size() && right_index < right.size()) {
        if (left[left_index] < right[right_index]) {
            array[original_index] = left[left_index];
            left_index++;
        } else {
            array[original_index] = right[right_index];
            right_index++;
        }
        original_index++;
    }

    while (left_index < left.size()) {
        array[original_index] = left[left_index];
        original_index++;
        left_index++;
    }

    while (right_index < right.size()) {
        array[original_index] = right[right_index];
        original_index++;
        right_index++;
    }
}
 
 int main() {
    std::srand(static_cast<unsigned>(std::time(0)));
    int size = 10;
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
        array[i] = std::rand() % 100;
    }
    
    std::cout << "Original array: ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    mergeSortHelper(array, 0, size - 1, 0);

    std::cout << "Sorted array: ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << "\n";
 
    return 0;
}
