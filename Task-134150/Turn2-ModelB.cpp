#include <vector>
#include <numeric>
#include <omp.h>

// ... (Same code as before)

int main() {
  const int numSamples = 1000000;
  std::vector<double> forces(numSamples);
  // Initialize forces data...

  // Using parallel accumulate to sum forces
  double totalForce = std::accumulate(forces.begin(), forces.end(), 0.0,
                    [&](double sum, double force) {
                      #pragma omp atomic
                      return sum + force;
                    });

  std::cout << "Total Force (Parallel): " << totalForce << std::endl;
  return 0;
}