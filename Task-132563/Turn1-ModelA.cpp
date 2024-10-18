#include <chrono>
#include <iostream>
#include <thread>

// Function to be timed
void criticalSection() {
  for (int i = 0; i < 1000000; i++) {
    // Simulate some work
    int a = 34;
    int b = 56;
    int c = a * b;
  }
}

int main() {
  const int num_iterations = 10;
  std::chrono::duration<double, std::nano> total_time =
      std::chrono::duration<double, std::nano>::zero();

  // Warm up the cache
  criticalSection();

  for (int i = 0; i < num_iterations; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    criticalSection();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    total_time += duration;
  }

  // Calculate average time
  auto average_time = total_time / num_iterations;

  std::cout << "Average execution time of criticalSection: "
            << average_time.count() << " nanoseconds" << std::endl;

  // Check for potential bottleneck
  const int threshold_ns = 100000; // Example threshold, adjust as needed
  if (average_time.count() > threshold_ns) {
    std::cout
        << "**Bottleneck detected! Average execution time exceeds threshold."
        << std::endl;
    // Now, you can investigate and resolve the bottleneck in the
    // criticalSection function
  }

  return 0;
}