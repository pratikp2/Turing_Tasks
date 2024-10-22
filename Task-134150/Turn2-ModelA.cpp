#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>

// Pure function to calculate drag coefficient
double calculateDragCoefficient(double speed, double area) {
  return 0.001 * speed * speed * area;
}

int main() {
  const double airDensity = 1.225;
  const double wingArea = 10.0;
  const size_t numVelocities = 1000000;
  std::vector<double> velocities(numVelocities);
  std::iota(velocities.begin(), velocities.end(), 0.0);

  // Using std::transform with std::execution::par to parallelize the calculation
  std::vector<double> dragCoefficients(numVelocities);
  std::transform(std::execution::par, velocities.begin(), velocities.end(), dragCoefficients.begin(),
         [=](double speed) { return calculateDragCoefficient(speed, wingArea); });

  double totalDrag = std::accumulate(dragCoefficients.begin(), dragCoefficients.end(), 0.0);

  std::cout << "Total Drag: " << totalDrag << std::endl;
  return 0;
}