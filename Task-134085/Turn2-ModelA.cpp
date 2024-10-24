#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>
#include <future>

// Function to process events
void ProcessEvents(const std::vector<int>& events, std::atomic<int>& processedEvents) {
  for (int event : events) {
    // Simulate some work for each event
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    processedEvents++;
  }
}

int main() {
  const int num_events = 100000; // Increased number of events for scaling
  const int num_threads = std::thread::hardware_concurrency(); // Use all available cores

  std::vector<int> events(num_events);
  std::atomic<int> processedEvents{0};

  // Warm up the function
  ProcessEvents(events, processedEvents);

  auto start = std::chrono::high_resolution_clock::now();

  // Create a vector of futures to manage threads
  std::vector<std::future<void>> futures;
  for (int i = 0; i < num_threads; ++i) {
    size_t start_idx = i * num_events / num_threads;
    size_t end_idx = (i + 1) * num_events / num_threads;
    futures.push_back(std::async(std::launch::async, ProcessEvents, std::vector<int>(events.begin() + start_idx, events.begin() + end_idx), std::ref(processedEvents)));
  }

  // Wait for all threads to complete
  for (auto& future : futures) {
    future.get();
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  std::cout << "Latency for processing " << num_events << " events with " << num_threads << " threads: " << duration << " microseconds" << std::endl;
  std::cout << "Total Events Processed: " << processedEvents << std::endl;

  return 0;
}