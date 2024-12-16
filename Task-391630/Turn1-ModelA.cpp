#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    // Define two sequences: values and weights
    std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> weights = {0.1, 0.2, 0.3, 0.4, 0.5};

    // Check if the sizes of both vectors are equal
    if (values.size() != weights.size()) {
        std::cerr << "Error: Mismatched sizes of values and weights." << std::endl;
        return 1;
    }

    // Create a container for the weighted products
    std::vector<double> weightedProducts(values.size());

    // Use std::transform to calculate weighted products
    std::transform(values.begin(), values.end(), weights.begin(), weightedProducts.begin(),
                   [](double value, double weight) {
                       return value * weight;
                   });

    // Now, use std::accumulate to sum the weighted products
    double weightedSum = std::accumulate(weightedProducts.begin(), weightedProducts.end(), 0.0);

    // Output the result
    std::cout << "Weighted Sum: " << weightedSum << std::endl;

    return 0;
}
