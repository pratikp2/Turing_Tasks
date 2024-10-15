#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// Define the objective functions
double performance_func(const vector<double>& data) {
	// Sample performance function: Sum of absolute differences
	return accumulate(data.begin(), data.end(), 0.0, [](double sum, double x) {
		return sum + abs(x);
	});
}

double output_quality_func(const vector<double>& data) {
	// Sample output quality function: Mean absolute error
	double sum = accumulate(data.begin(), data.end(), 0.0, [](double sum, double x) {
		return sum + abs(x);
	});
	return sum / data.size();
}

// Multi-objective optimization function
vector<double> optimize(const vector<double>& input_data, double weight_performance, double weight_quality) {
	const int num_iterations = 1000; // You can adjust the number of iterations
	const double mutation_rate = 0.01;
	const int population_size = 100;

	vector<vector<double>> population(population_size, input_data);

	for (int iteration = 0; iteration < num_iterations; iteration++) {
		for (int i = 0; i < population_size; i++) {
			vector<double> child = population[i];
			for (int j = 0; j < child.size(); j++) {
				if (rand() / (RAND_MAX + 1.0) < mutation_rate) {
					child[j] += (rand() / (RAND_MAX + 1.0) - 0.5) * 0.1;
				}
			}

			double perf = performance_func(child);
			double qual = output_quality_func(child);
			double fitness = weight_performance * perf + weight_quality * qual;

			for (int j = 0; j < population_size; j++) {
				double other_fitness = weight_performance * performance_func(population[j]) + weight_quality * output_quality_func(population[j]);
				if (fitness < other_fitness) {
					population[j] = child;
					break;
				}
			}
		}
	}

	// Find the individual with the best fitness in the final population
	vector<double> best_individual = population[0];
	double best_fitness = weight_performance * performance_func(best_individual) + weight_quality * output_quality_func(best_individual);
	for (int i = 1; i < population_size; i++) {
		double fitness = weight_performance * performance_func(population[i]) + weight_quality * output_quality_func(population[i]);
		if (fitness < best_fitness) {
			best_individual = population[i];
			best_fitness = fitness;
		}
	}

	return best_individual;
}

int main() {
	vector<double> input_data = {1.2, 3.4, -5.6, 7.8, -2.3, 4.5, 6.7};

	// Tweak the weightage factors to prioritize output quality
	double weight_performance = 0.3; // You can adjust these values
	double weight_quality = 0.7;

	vector<double> optimized_data = optimize(input_data, weight_performance, weight_quality);

	// Display the optimized data
	cout << "Optimized Data: [";
	for (size_t i = 0; i < optimized_data.size(); i++) {
		if (i != 0) cout << ", ";
		cout << optimized_data[i];
	}
	cout << "]" << endl;
	return 0;
}