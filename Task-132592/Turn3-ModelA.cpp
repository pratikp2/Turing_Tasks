#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

// ... (Same code as before)

const int NUM_DATA_POINTS = 1_000_000;
const int NUM_THREADS = 4;

void processDataStream(AuditingManager &manager) {
  for (int i = 0; i < NUM_DATA_POINTS; ++i) {
    manager.auditData(i);
  }
}

int main() {
  AuditingManager manager;
  // ... (Add auditing rules)

  // Warm up the cache
  processDataStream(manager);

  std::vector<std::thread> threads;
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.push_back(std::thread(processDataStream, std::ref(manager)));
  }

  auto start = std::chrono::high_resolution_clock::now();

  for (auto &thread : threads) {
    thread.join();
  }

  auto end = std::chrono::high_resolution_clock::now();

  double duration =
      std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
          .count();
  std::cout << "Processing time: " << duration << " seconds" << std::endl;
  std::cout << "Data points processed per second: "
            << static_cast<double>(NUM_DATA_POINTS * NUM_THREADS) / duration
            << std::endl;

  return 0;
}