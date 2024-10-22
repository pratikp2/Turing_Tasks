#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Pure function to calculate drag coefficient
double calculateDragCoefficient(double speed, double area) {
  return 0.001 * speed * speed * area;
}

// Pure function to apply lift formula
double applyLiftFormula(double density, double area, double velocity) {
  return 0.5 * density * velocity * velocity * area;
}

// Lazy evaluated function to sum up forces (using std::accumulate)
double sumForces(const std::vector<double>& forces) {
  return std::accumulate(forces.begin(), forces.end(), 0.0);
}

int main() {
  const double airDensity = 1.225;
  const double wingArea = 10.0;
  const std::vector<double> velocities = {10.0, 20.0, 30.0, 40.0, 50.0};

  // Using map and transform to apply functions on each element and create new vectors
  std::vector<double> dragCoefficients;
  std::transform(velocities.begin(), velocities.end(), std::back_inserter(dragCoefficients),
         [=](double speed) { return calculateDragCoefficient(speed, wingArea); });

  std::vector<double> lifts;
  std::transform(velocities.begin(), velocities.end(), std::back_inserter(lifts),
         [=](double speed) { return applyLiftFormula(airDensity, wingArea, speed); });

  // Calculating total drag and lift using sumForces
  double totalDrag = sumForces(dragCoefficients);
  double totalLift = sumForces(lifts);

  std::cout << "Total Drag: " << totalDrag << std::endl;
  std::cout << "Total Lift: " << totalLift << std::endl;
  return 0;
}