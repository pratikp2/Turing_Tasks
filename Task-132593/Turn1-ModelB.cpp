
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

// Helper function to calculate the energy of a configuration
double calculateEnergy(const std::vector<int>& configuration, double J) {
    double energy = 0.0;
    for (size_t i = 0; i < configuration.size(); ++i) {
        energy -= J * configuration[i] * (configuration[(i + 1) % configuration.size()] + configuration[(i - 1 + configuration.size()) % configuration.size()]);
    }
    return energy;
}

// Metropolis Algorithm function
void metropolisAlgorithm(std::vector<int>& configuration, double J, double beta, int steps) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double initialEnergy = calculateEnergy(configuration, J);

    for (int i = 0; i < steps; ++i) {
        int randomIndex = std::rand() % configuration.size();
        configuration[randomIndex] = -configuration[randomIndex];

        double deltaEnergy = 2 * J * configuration[randomIndex] * (configuration[(randomIndex + 1) % configuration.size()] + configuration[(randomIndex - 1 + configuration.size()) % configuration.size()]);

        if (deltaEnergy < 0 || dis(gen) < std::exp(-beta * deltaEnergy)) {
            // Accept the change
        } else {
            // Reject the change and restore the original configuration
            configuration[randomIndex] = -configuration[randomIndex];
        }
    }
}

int main() {
    const int L = 100; // System size
    double J = 1.0; // Coupling constant
    double beta = 1.0; // Inverse temperature
    int steps = 100000; // Number of Monte Carlo steps

    // Initialize the configuration with random spins
    std::vector<int> configuration(L, 0);
    for (size_t i = 0; i < configuration.size(); ++i) {
        configuration[i] = (std::rand() % 2 == 0) ? 1 : -1;
    }

    // Apply the Metropolis Algorithm
    metropolisAlgorithm(configuration, J, beta, steps);

    // Calculate and print the final magnetization
    double magnetization = std::accumulate(configuration.begin(), configuration.end(), 0.0);
    magnetization /= static_cast<double>(configuration.size());
    std::cout << "Final Magnetization: " << magnetization << std::endl;

    return 0;
}

