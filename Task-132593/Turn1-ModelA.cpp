#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Function to calculate the acceptance probability
double acceptanceProbability(double deltaE, double temperature) {
  return std::min(1.0, std::exp(-deltaE / temperature));
}

// Metropolis Hastings Algorithm for simulating urban dynamics
void metropolisHastings(int numAgents, int numIterations, double temperature) {
  std::vector<int> agentPositions(numAgents, 0); // Initialize agent positions
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, numAgents - 1);

  for (int iteration = 0; iteration < numIterations; iteration++) {
    int agentIndex = dist(gen);
    int newPosition = (agentPositions[agentIndex] + 1) % numAgents; // Move the agent to the next position (wrapping around)

    double deltaE = 0.0; // Calculate the energy change (for simplicity, we'll use 0 here)

    double acceptanceRate = acceptanceProbability(deltaE, temperature);
    if (std::uniform_real_distribution<>(0.0, 1.0)(gen) < acceptanceRate) {
      agentPositions[agentIndex] = newPosition;
    }
  }

  // Process the final agent positions after all iterations
  // For example, you can calculate average agent distance or clustering coefficients
}

int main() {
  const int numAgents = 100;
  const int numIterations = 100000;
  const double temperature = 1.0; // Adjust temperature as needed

  auto start = std::chrono::high_resolution_clock::now();

  metropolisHastings(numAgents, numIterations, temperature);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

  std::cout << "Simulation completed in: " << time_span.count() << " seconds" << std::endl;
  return 0;
}