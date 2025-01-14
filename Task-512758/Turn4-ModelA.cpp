#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

// Define an interface for risk calculation strategies
class RiskCalculator {
public:
    virtual double calculate(const std::vector<double>& data) const = 0;
    virtual ~RiskCalculator() = default;
};

// Custom exception for missing strategies
class MissingStrategyException : public std::runtime_error {
public:
    MissingStrategyException() : std::runtime_error("Error: Missing risk calculation strategy.") {}
};

// Custom exception for invalid data
class InvalidDataException : public std::runtime_error {
public:
    InvalidDataException() : std::runtime_error("Error: Invalid data provided for risk calculation.") {}
};

// Concrete implementation of risk calculation - Value at Risk (VaR)
class VaRCalculator : public RiskCalculator {
public:
    double calculate(const std::vector<double>& data) const override {
        if (data.empty()) {
            throw InvalidDataException();
        }
        return *std::max_element(data.begin(), data.end()) * 0.95;
    }
};

// Another concrete implementation - Standard Deviation
class StdDevCalculator : public RiskCalculator {
public:
    double calculate(const std::vector<double>& data) const override {
        if (data.empty()) {
            throw InvalidDataException();
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
    if (!calculator) {
        throw MissingStrategyException();
    }

    for (const auto& portfolio : portfolios) {
        try {
            double risk = calculator->calculate(portfolio);
            std::cout << "Calculated Risk: " << risk << std::endl;
        } catch (const InvalidDataException& e) {
            std::cerr << e.what() << " Skipping this portfolio." << std::endl;
        }
    }
}

int main() {
    // Example portfolios
    std::vector<std::vector<double>> portfolios = {
        {100.0, 102.0, 105.0, 98.0},
        {}, // This portfolio is empty and should trigger an exception
        {200.0, 210.0, 205.0, 202.0, 212.0}
    };

    // Switch between strategies dynamically
    std::shared_ptr<RiskCalculator> currentStrategy;

    try {
        // Using Value at Risk (VaR) strategy
        currentStrategy = std::make_shared<VaRCalculator>();
        std::cout << "Using VaRCalculator:" << std::endl;
        processPortfolios(portfolios, currentStrategy);

        // Now switching to Standard Deviation strategy
        currentStrategy = std::make_shared<StdDevCalculator>();
        std::cout << "Using StdDevCalculator:" << std::endl;
        processPortfolios(portfolios, currentStrategy);
        
        // Simulating missing strategies case
        currentStrategy = nullptr; // Simulate missing strategy
        std::cout << "Using MissingStrategy:" << std::endl;
        processPortfolios(portfolios, currentStrategy);
    } catch (const MissingStrategyException& e) {
        std::cerr << e.what() << std::endl; // Handle missing strategy exception
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl; // General error handling
    }

    return 0;
}
