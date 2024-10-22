#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Pure function to calculate drag coefficient
double calculateDragCoefficient(double speed, double area) {
  return 0.001 * speed * speed * area;
}

// Pure function to apply lift formula
double applyLiftFormula(double density, double area, double velocity) {
  return 0.5 * density * velocity * velocity * area;
}

// Higher-order function to calculate forces
std::vector<double> calculateForces(const std::vector<double>& velocities, std::function<double(double, double)> forceFunction, double param1, double param2) {
  std::vector<double> forces(velocities.size());
  std::transform(velocities.begin(), velocities.end(), forces.begin(), [&](double velocity) {
    return forceFunction(velocity, param1, param2);
  });
  return forces;
}

int main() {
  const double airDensity = 1.225;
  const double wingArea = 10.0;
  const std::vector<double> velocities = {10.0, 20.0, 30.0, 40.0, 50.0};

  // Calculating drag forces using calculateForces
  auto dragForces = calculateForces(velocities, calculateDragCoefficient, wingArea, /* dummy param for lift */ 0.0);

  // Calculating lift forces using calculateForces
  auto liftForces = calculateForces(velocities, applyLiftFormula, airDensity, wingArea);

  // Calculating total drag and lift
  double totalDrag = std::accumulate(dragForces.begin(), dragForces.end(), 0.0);
  double totalLift = std::accumulate(liftForces.begin(), liftForces.end(), 0.0);

  std::cout << "Total Drag: " << totalDrag << std::endl;
  std::cout << "Total Lift: " << totalLift << std::endl;
  return 0;
}