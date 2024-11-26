
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <benchmark/benchmark.h>
#include <gperftools/tcmalloc.h>

// Define the number of threads and the number of allocations per thread
constexpr int kNumThreads = 4;
constexpr int kAllocationsPerThread = 1000000;

// Function to perform allocations and deallocations using the default allocator
void AllocatorDefault(benchmark::State& state) {
    while (state.KeepRunning()) {
        std::vector<char*> allocations;
        for (int i = 0; i < kAllocationsPerThread; ++i) {
            char* ptr = new char[100];
            allocations.push_back(ptr);
        }
        for (char* ptr : allocations) {
            delete[] ptr;
        }
    }
}

// Function to perform allocations and deallocations using tcmalloc
void AllocatorTCMalloc(benchmark::State& state) {
    while (state.KeepRunning()) {
        std::vector<char*> allocations;
        for (int i = 0; i < kAllocationsPerThread; ++i) {
            char* ptr = (char*)tcmalloc::Malloc(100);
            allocations.push_back(ptr);
        }
        for (char* ptr : allocations) {
            tcmalloc::Free(ptr);
        }
    }
}

// Register the benchmark functions
BENCHMARK(AllocatorDefault);
BENCHMARK(AllocatorTCMalloc);

BENCHMARK_MAIN();
