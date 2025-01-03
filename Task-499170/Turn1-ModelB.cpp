#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include <random>

const int BUFFER_SIZE = 1024 * 1024;  // 1 MB buffer size
const int NUM_ITERATIONS = 1000000;

void measureStrCpyPerformance() {
    std::string source(BUFFER_SIZE, 'a');
    std::string destination;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        destination.copy(source.data(), source.size(), 0);
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double latency = static_cast<double>(duration.count()) / NUM_ITERATIONS;
    double throughput = static_cast<double>(BUFFER_SIZE) / (latency / 1000.0); // in KB/s

    std::cout << "strcpy (std::string::copy) Performance:" << std::endl;
    std::cout << "Latency: " << latency << " microseconds per copy" << std::endl;
    std::cout << "Throughput: " << throughput << " KB/s" << std::endl;
}

void measureStrLenPerformance() {
    std::string data(BUFFER_SIZE, 'a');

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        size_t len = data.size();
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
    double latency = static_cast<double>(duration.count()) / NUM_ITERATIONS;

    std::cout << "strlen (std::string::size) Performance:" << std::endl;
    std::cout << "Latency: " << latency << " microseconds per length calculation" << std::endl;
}

int main() {
    measureStrCpyPerformance();
    measureStrLenPerformance();
    return 0;
}
