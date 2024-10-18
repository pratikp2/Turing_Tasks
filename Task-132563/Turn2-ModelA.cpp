#include <iostream>
#include <chrono>
#include <vector>
#include <string>

// Function prototypes for the code segments to be measured
void compute_heavy_task1(int n);
void compute_heavy_task2(int n);
void compute_heavy_task3(int n);

// Structure to store timing information for each code segment
struct TimedSegment {
  std::string name;
  double time_taken_ms;
};

int main() {
  int task_size = 100000; // Adjust this as needed
  std::vector<TimedSegment> timed_segments;

  // Initialize the vector with names of code segments to be measured
  timed_segments = {
    {"compute_heavy_task1", 0},
    {"compute_heavy_task2", 0},
    {"compute_heavy_task3", 0}
  };

  for (size_t i = 0; i < timed_segments.size(); ++i) {
    std::chrono::steady_clock::time_point start, end;

    // Measure the time taken by each code segment
    start = std::chrono::steady_clock::now();
    if (i == 0) {
      compute_heavy_task1(task_size);
    } else if (i == 1) {
      compute_heavy_task2(task_size);
    } else {
      compute_heavy_task3(task_size);
    }
    end = std::chrono::steady_clock::now();

    // Calculate the execution time in milliseconds and store it in the vector
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    timed_segments[i].time_taken_ms = time_taken;
  }

  // Display the results
  std::cout << "Performance Analysis:" << std::endl;
  for (const TimedSegment& segment : timed_segments) {
    std::cout << "Function: " << segment.name << ", Execution time: " << segment.time_taken_ms << " milliseconds" << std::endl;
  }

  return 0;
}

 // Define the implementations of the code segments here
void compute_heavy_task1(int n) {
  // Implementation of heavy task 1
}

void compute_heavy_task2(int n) {
  // Implementation of heavy task 2
}

void compute_heavy_task3(int n) {
  // Implementation of heavy task 3
}