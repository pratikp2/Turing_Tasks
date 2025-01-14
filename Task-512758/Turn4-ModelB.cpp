#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> // For std::max_element and std::for_each
#include <numeric>   // For std::accumulate
#include <cmath>     // For std::sqrt
#include <stdexcept> // For custom exceptions
#include <unordered_map> // For strategy registry

// Define an interface for risk calculation strategies
class RiskCalculator {
public:
    virtual double calculate(const std::vector<double>& data) const = 0;
    virtual ~RiskCalculator() = default;
};

// Concrete implementation of risk calculation - Value at Risk (VaR)
class VaRCalculator : public RiskCalculator {
public:
    double calculate(const std::vector<double>& data) const override {
        if (data.empty()) {
            throw std::invalid_argument("Input data for VaR calculation is empty.");
        }
        // Implement a simple VaR calculation (placeholder logic)
        return *std::max_element(data.begin(), data.end()) * 0.95;
    }
};

// Another concrete implementation - Standard Deviation
class StdDevCalculator : public RiskCalculator {
public:
    double calculate(const std::vector<double>& data) const override {
        if (data.size() < 2) {
            throw std::invalid_argument("Input data for StdDev calculation should have at least 2 elements.");
        }
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double accum = 0.0;
        std::for_each(data.begin(), data.end(), [&](double d) {
            accum += (d - mean) * (d - mean);
        });
        return std::sqrt(accum / (data.size() - 1));
    }
};

// Function to process portfolios with dynamic strategy injection
void processPortfolios(const std::vector<std::vector<double>>& portfolios,
                       const std::shared_ptr<RiskCalculator>& calculator) {
    for (const auto& portfolio : portfolios) {
        try {
            double risk = calculator->calculate(portfolio);
            std::cout << "Calculated Risk: " << risk << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

// Create a registry for strategies
class StrategyRegistry {
public:
    void registerStrategy(const std::string& name, const std::shared_ptr<RiskCalculator>& strategy) {
        strategies[name] = strategy;
    }

    std::shared_ptr<RiskCalculator> getStrategy(const std::string& name) const {
        auto it = strategies.find(name);
        if (it == strategies.end()) {
            throw std::runtime_error("Strategy not found: " + name);
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<RiskCalculator>> strategies;
};

int main() {
    // Example portfolios
    std::vector<std::vector<double>> portfolios = {
        {100.0, 102.0, 105.0, 98.0},
        {200.0},
        {},
        {200.0, 210.0, 205.0, 202.0, 212.0}
    };

    // Strategy Registry
    StrategyRegistry registry;
    registry.registerStrategy("var", std::make_shared<VaRCalculator>());
    registry.registerStrategy("stddev", std::make_shared<StdDevCalculator>());

    // Switch between strategies dynamically using registry
    try {
        std::cout << "Using VaRCalculator:" << std::endl;
        processPortfolios(portfolios, registry.getStrategy("var"));

        std::cout << "Using StdDevCalculator:" << std::endl;
        processPortfolios(portfolios, registry.getStrategy("stddev"));

        // Try using an invalid strategy name
        processPortfolios(portfolios, registry.getStrategy("invalid_strategy"));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
