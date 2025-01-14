#include <iostream>
#include <vector>
#include <memory>

// Define an interface for risk calculation
class RiskCalculator {
public:
    virtual double calculate(const std::vector<double>& data) const = 0;
    virtual ~RiskCalculator() = default;
};

// Concrete implementation of risk calculation - Value at Risk (VaR)
class VaRCalculator : public RiskCalculator {
public:
    double calculate(const std::vector<double>& data) const override {
        // Implement a simple VaR calculation (placeholder logic)
        return *std::max_element(data.begin(), data.end()) * 0.95;
    }
};

// Another concrete implementation - Standard Deviation
class StdDevCalculator : public RiskCalculator {
public:
    double calculate(const std::vector<double>& data) const override {
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double accum = 0.0;
        std::for_each(data.begin(), data.end(), [&](double d) {
            accum += (d - mean) * (d - mean);
        });
        return std::sqrt(accum / (data.size() - 1));
    }
};

// Function to process portfolios with dependency injection
void processPortfolios(const std::vector<std::vector<double>>& portfolios,
                       const RiskCalculator& calculator) {
    for (const auto& portfolio : portfolios) {
        double risk = calculator.calculate(portfolio);
        std::cout << "Calculated Risk: " << risk << std::endl;
    }
}

int main() {
    // Example portfolios
    std::vector<std::vector<double>> portfolios = {
        {100.0, 102.0, 105.0, 98.0},
        {200.0, 210.0, 205.0, 202.0, 212.0}
    };

    // Use the VaRCalculator
    VaRCalculator varCalculator;
    processPortfolios(portfolios, varCalculator);

    // Now, if we want to switch to StdDevCalculator
    StdDevCalculator stdDevCalculator;
    processPortfolios(portfolios, stdDevCalculator);

    return 0;
}
