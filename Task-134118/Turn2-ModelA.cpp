#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mtx;
std::atomic<int> sharedCounter{0};

void incrementCounter(int num_increments) {
  for (int i = 0; i < num_increments; i++) {
    mtx.lock();
    sharedCounter++;
    mtx.unlock();
  }
}

int main() {
  const int num_threads = 4;
  const int num_increments_per_thread = 1000000;

  std::thread threads[num_threads];

  // Start threads
  for (int i = 0; i < num_threads; i++) {
    threads[i] = std::thread(incrementCounter, num_increments_per_thread);
  }

  // Join threads
  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }

  std::cout << "Final Counter Value: " << sharedCounter << std::endl;
  return 0;
}