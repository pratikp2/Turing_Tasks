#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> // For std::max_element
#include <numeric>   // For std::accumulate
#include <cmath>     // For std::sqrt

// Define an interface for risk calculation strategies
class RiskStrategy {
public:
    virtual double calculateRisk(const std::vector<double>& assetValues) const = 0;
    virtual ~RiskStrategy() = default;
};

// Concrete implementations of risk calculation strategies
class VaRStrategy : public RiskStrategy {
public:
    double calculateRisk(const std::vector<double>& assetValues) const override {
        // Implement a simple VaR calculation (placeholder logic)
        return *std::max_element(assetValues.begin(), assetValues.end()) * 0.95;
    }
};

class StdDevStrategy : public RiskStrategy {
public:
    double calculateRisk(const std::vector<double>& assetValues) const override {
        double mean = std::accumulate(assetValues.begin(), assetValues.end(), 0.0) / assetValues.size();
        double sumSquaredDifferences = 0.0;
        for (double value : assetValues) {
            double diff = value - mean;
            sumSquaredDifferences += diff * diff;
        }
        return std::sqrt(sumSquaredDifferences / (assetValues.size() - 1));
    }
};

// Function to process portfolios using a given risk strategy
void processPortfolios(const std::vector<std::vector<double>>& portfolios, const std::unique_ptr<RiskStrategy>& strategy) {
    for (const auto& portfolio : portfolios) {
        double risk = strategy->calculateRisk(portfolio);
        std::cout << "Calculated Risk: " << risk << std::endl;
    }
}

int main() {
    // Example portfolios
    std::vector<std::vector<double>> portfolios = {
        {100.0, 102.0, 105.0, 98.0},
        {200.0, 210.0, 205.0, 202.0, 212.0}
    };

    // Use VaRStrategy
    std::unique_ptr<RiskStrategy> varStrategy = std::make_unique<VaRStrategy>();
    processPortfolios(portfolios, varStrategy);

    // Switch to StdDevStrategy
    std::unique_ptr<RiskStrategy> stdDevStrategy = std::make_unique<StdDevStrategy>();
    processPortfolios(portfolios, stdDevStrategy);

    return 0;
}
