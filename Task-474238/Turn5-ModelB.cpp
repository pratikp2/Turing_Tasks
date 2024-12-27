#include <benchmark/benchmark.h>

void BM_SufficiencyConstraint(benchmark::State& state) {
    for (auto _ : state) {
        // Your code to be benchmarked here
    }
}
BENCHMARK(BM_SufficiencyConstraint);

int main(int argc, char** argv) {
    ::benchmark::Initialise(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}
#include <cppbenchmark/cppbenchmark.h>

void BM_SufficiencyConstraint(cppbm::State& state) {
    for (auto _ : state) {
        // Your code to be benchmarked here
    }
}
CPPBENCHMARK(BM_SufficiencyConstraint);

int main(int argc, char** argv) {
    cppbm::RunAll(argc, argv);
    return 0;
}
