#include <iostream>
#include <vector>
#include <memory>

// Base interface for algorithms
class Algorithm {
public:
    virtual ~Algorithm() {}
    virtual int processData(const std::vector<int>& data) const = 0;
};

// Algorithm implementation 1: Bubble Sort
class BubbleSort : public Algorithm {
public:
    int processData(const std::vector<int>& data) const override {
        int n = data.size();
        bool swapped;
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
        return n;
    }
};

// Algorithm implementation 2: Quick Sort
class QuickSort : public Algorithm {
public:
    int processData(const std::vector<int>& data) const override {
        int n = data.size();
        std::vector<int> temp(data);
        quickSort(temp, 0, n - 1);
        return n;
    }

private:
    void quickSort(std::vector<int>& arr, int left, int right) const {
        if (left < right) {
            int pi = partition(arr, left, right);
            quickSort(arr, left, pi - 1);
            quickSort(arr, pi + 1, right);
        }
    }

    int partition(std::vector<int>& arr, int left, int right) const {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]);
        return i + 1;
    }
};

// Factory for algorithms
class AlgorithmFactory {
public:
    static std::unique_ptr<Algorithm> createAlgorithm(const std::string& type) {
        if (type == "BubbleSort") {
            return std::make_unique<BubbleSort>();
        } else if (type == "QuickSort") {
            return std::make_unique<QuickSort>();
        } else {
            throw std::invalid_argument("Unknown algorithm type");
        }
    }
};

// Main function to test the factory
int main() {
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Data: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    try {
        std::unique_ptr<Algorithm> algorithm = AlgorithmFactory::createAlgorithm("QuickSort");
        int swaps = algorithm->processData(data);
        std::cout << "Sorted data: ";
        for (int num : data) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << "Number of swaps: " << swaps << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}