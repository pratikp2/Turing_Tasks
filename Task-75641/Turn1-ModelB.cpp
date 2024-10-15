
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

// Sample data scrubbing function
// This function takes a dataset and a threshold as input
// and returns the cleaned dataset and the number of records scrubbed.
std::pair<std::vector<int>, size_t> scrubData(const std::vector<int>& dataset, int threshold) {
    std::vector<int> cleanedData;
    size_t scrubbedCount = 0;

    for (const int& data : dataset) {
        if (data >= threshold) {
            cleanedData.push_back(data);
        } else {
            scrubbedCount++;
        }
    }
    return {cleanedData, scrubbedCount};
}

// Function to calculate the first objective: Performance - Scrubbing time
double calculatePerformance(const std::vector<int>& dataset, int threshold) {
    // Measure the scrubbing time
    auto start = std::chrono::high_resolution_clock::now();
    scrubData(dataset, threshold);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    return time_span.count();
}

// Function to calculate the second objective: Output Quality - Percentage of clean data
double calculateOutputQuality(const std::vector<int>& dataset, int threshold) {
    auto [cleanedData, scrubbedCount] = scrubData(dataset, threshold);
    double quality = 100.0 * static_cast<double>(cleanedData.size()) / dataset.size();
    return quality;
}

// Multi-objective fitness function: Weighted sum of objectives
double calculateFitness(const std::vector<int>& dataset, int threshold, double weight_performance, double weight_quality)
{
    double performance = calculatePerformance(dataset, threshold);
    double output_quality = calculateOutputQuality(dataset, threshold);

    // Define the fitness function as a weighted sum of objectives
    return weight_performance * performance + weight_quality * output_quality;
}

// Genetic Algorithm parameters
const int populationSize = 100;
const int numGenerations = 100;
const double mutationRate = 0.01;
const double crossoverRate = 0.7;

int main() {
    // Generate random dataset for demonstration purposes
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    const size_t datasetSize = 10000;
    std::vector<int> dataset(datasetSize);
    std::generate(dataset.begin(), dataset.end(), [&] { return dis(gen); });

    // Initial population of thresholds
    std::vector<int> population(populationSize);
    std::generate(population.begin(), population.end(), [&] { return dis(gen) % 100; });

    // Define the weights for the two objectives
    double weight_performance = 0.5; // You can change these values to experiment
    double weight_quality = 0.5;

    for (int generation = 0; generation < numGenerations; generation++) {
        // Calculate fitness for each individual in the population
        std::vector<double> fitness(populationSize);
        std::transform(population.begin(), population.end(), fitness.begin(), [&](int threshold) {
            return calculateFitness(dataset, threshold, weight_performance, weight_quality);
        });

        // Select parents for crossover
        std::vector<int> parents(populationSize);
        std::partial_sort_copy(population.begin(), population.end(), parents.begin(), parents.end(), [&](int a, int b) {
            return fitness[a] > fitness[b];
        });

        // Crossover to create offspring
        std::vector<int> offspring(populationSize);
        for (int i = 0; i < populationSize; i += 2) {
            int parent1 = parents[i];
            int parent2 = parents[i + 1];

            if (static_cast<double>(rd()) / RAND_MAX < crossoverRate) {
                int crossoverPoint = dis(gen) % 100;
                offspring[i] = (parent1 & ((1 << crossoverPoint) - 1)) | (parent2 & ~((1 << crossoverPoint) - 1));
                offspring[i + 1] = (parent2 & ((1 << crossoverPoint) - 1)) | (parent1 & ~((1 << crossoverPoint) - 1));
            } else {
                offspring[i] = parent1;
                offspring[i + 1] = parent2;
            }
        }

        // Mutation
        for (int i = 0; i < populationSize; i++) {
            if (static_cast<double>(rd()) / RAND_MAX < mutationRate) {
                offspring[i] = (offspring[i] + dis(gen) % 20 - 10) % 100;
            }
        }

        population = offspring;
    }

    // Find the best solution in the final population
    int bestThreshold = *std::max_element(population.begin(), population.end(), [&](int a, int b) {
        return calculateFitness(dataset, a, weight_performance, weight_quality) < calculateFitness(dataset, b, weight_performance, weight_quality);
    });

    // Display the results
    std::cout << "Best Threshold: " << bestThreshold << std::endl;
    auto [cleanedData, scrubbedCount] = scrubData(dataset, bestThreshold);
    double finalQuality = 100.0 * static_cast<double>(cleanedData.size()) / dataset.size();
    std::cout << "Scrubbed Records: " << scrubbedCount << std::endl;
    std::cout << "Final Output Quality: " << finalQuality << "%" << std::endl;

    return 0;
}  
                        