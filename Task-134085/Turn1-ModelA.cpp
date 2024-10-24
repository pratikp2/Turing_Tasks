#include <iostream>
#include <chrono>
#include <vector>

// Function to process events (replace this with the actual event processing function)
void ProcessEvents(const std::vector<int>& events) {
  for (int event : events) {
    // Simulate some work for each event
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

int main() {
  const int num_events = 1000;
  std::vector<int> events(num_events);

  // Warm up the function
  ProcessEvents(events);

  auto start = std::chrono::high_resolution_clock::now();

  ProcessEvents(events);

  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  std::cout << "Latency for processing " << num_events << " events: " << duration << " microseconds" << std::endl;
  return 0;
}