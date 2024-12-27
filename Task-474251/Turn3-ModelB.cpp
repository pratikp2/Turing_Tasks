#include <iostream>
#include <thread>
#include <future>
#include <algorithm>
#include <vector>

const int N = 10000;

void calculateSquare(int x, int& result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result += x * x;
        }
    }
}

int main() {
    int result_1 = 0, result_2 = 0;
    // Synchronous execution
    std::cout << "Synchronous execution:\n";
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        calculateSquare(1, result_1);
        calculateSquare(2, result_2);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
    }
    // Asynchronous execution with std::async
    std::cout << "\nAsynchronous execution with std::async:\n";
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        std::future<void> task1 = std::async(std::launch::async, calculateSquare, 1, std::ref(result_1));
        std::future<void> task2 = std::async(std::launch::async, calculateSquare, 2, std::ref(result_2));
        task1.get();
        task2.get();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
    }
    return 0;
}
