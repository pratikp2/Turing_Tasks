#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <future>

const int NUM_THREADS = 4; // Number of parallel threads

// Function to process events (replace this with the actual event processing function)
void ProcessEvents(const std::vector<int>& events) {
  for (int event : events) {
    // Simulate some work for each event
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

int main() {
  const int num_events = 10000; // Total number of events
  std::vector<int> events(num_events);

  // Warm up the function
  ProcessEvents(events);

  // Divide the events into sub-vectors for parallel processing
  std::vector<std::vector<int>> event_chunks(NUM_THREADS);
  for (int i = 0; i < num_events; ++i) {
    event_chunks[i % NUM_THREADS].push_back(events[i]);
  }

  auto start = std::chrono::high_resolution_clock::now();

  // Start multiple threads to process events in parallel
  std::vector<std::future<void>> futures;
  for (int i = 0; i < NUM_THREADS; ++i) {
    futures.push_back(std::async(std::launch::async, ProcessEvents, std::cref(event_chunks[i])));
  }

  // Wait for all threads to complete
  for (int i = 0; i < NUM_THREADS; ++i) {
    futures[i].get();
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  std::cout << "Latency for processing " << num_events << " events with " << NUM_THREADS << " threads: " << duration << " microseconds" << std::endl;
  return 0;
}  