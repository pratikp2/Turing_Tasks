#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

void countSetBits(const std::vector<int>& data, int start, int end, std::atomic<int>& totalSetBits) {
    int count = 0;
    for (int i = start; i < end; ++i) {
        // Count set bits using Brian Kernighan's algorithm
        int n = data[i];
        while (n) {
            n &= (n - 1); // Clear the least significant bit set
            count++;
        }
    }
    totalSetBits += count;
}

int main() {
    std::vector<int> data = { 3, 5, 7, 15, 31, 1023 }; // Example data
    const int numThreads = std::thread::hardware_concurrency(); // Get number of available threads
    std::vector<std::thread> threads;
    std::atomic<int> totalSetBits{0}; // Atomic counter to avoid race conditions

    int n = data.size();
    int chunkSize = (n + numThreads - 1) / numThreads; // Determine chunk size for each thread

    // Spawn threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = std::min(start + chunkSize, n);
        if (start < n) {
            threads.emplace_back(countSetBits, std::ref(data), start, end, std::ref(totalSetBits));
        }
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Total number of set bits: " << totalSetBits.load() << std::endl;
    return 0;
}
