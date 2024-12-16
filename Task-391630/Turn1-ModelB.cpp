#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Sample data: two sequences and their corresponding weights
    std::vector<double> seq1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> seq2 = {5.0, 6.0, 7.0, 8.0};
    std::vector<double> weights = {0.2, 0.3, 0.4, 0.1};

    // Ensure the sequences and weights have the same size
    if (seq1.size() != seq2.size() || seq1.size() != weights.size()) {
        std::cerr << "Error: Sequences and weights must have the same size." << std::endl;
        return 1;
    }

    // Using std::transform to calculate element-wise products of sequences and weights
    std::vector<double> weighted_elements(seq1.size());
    std::transform(seq1.begin(), seq1.end(), weights.begin(), weighted_elements.begin(),
                    [](double x, double y) { return x * y; });

    // Using std::transform to calculate element-wise products of seq2 and weights
    std::transform(seq2.begin(), seq2.end(), weights.begin(), std::back_inserter(weighted_elements),
                    [](double x, double y) { return x * y; });

    // Using std::accumulate to calculate the weighted sum
    double weighted_sum = std::accumulate(weighted_elements.begin(), weighted_elements.end(), 0.0);

    // Display the result
    std::cout << "Weighted sum: " << weighted_sum << std::endl;

    return 0;
}
