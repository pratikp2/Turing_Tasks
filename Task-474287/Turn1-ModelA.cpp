#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

const int N = 100;
const int M = 100;

double approximateFunction(int i, int j) {
    // A costly operation we want to approximate
    // Let's say instead of doing sqrt(i*j) we just return 0.5*i + 0.5*j
    return 0.5 * i + 0.5 * j; // Approximation
}

void computePartial(int startRow, int endRow, std::vector<double> &results) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < M; ++j) {
            results[i] += approximateFunction(i, j);
        }
    }
}

int main() {
    std::vector<double> results(N, 0);
    
    // Create threads to handle computation
    std::vector<std::thread> threads;
    int numThreads = 4;
    int rowsPerThread = N / numThreads;
    
    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t + 1) * rowsPerThread;
        threads.push_back(std::thread(computePartial, startRow, endRow, std::ref(results)));
    }
    
    // Wait for all threads to complete
    for (auto &thread : threads) {
        thread.join();
    }
    
    // Final result before approximation
    double total = std::accumulate(results.begin(), results.end(), 0.0);
    std::cout << "Total result: " << total << std::endl;
    
    return 0;
}
