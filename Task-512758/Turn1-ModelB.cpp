class PortfolioAnalyzer {
public:
    PortfolioAnalyzer(const std::vector<std::vector<double>>& portfolios)
        : portfolios_(portfolios)
    {
    }
    void analyzePortfolios() const {
        for (const std::vector<double>& portfolio : portfolios_) {
            Calculator calculator(portfolio);
            double total = calculator.calculateTotal();
            double mean = calculator.calculateMean();
            std::cout << "Portfolio total: " << total << ", Mean: " << mean << std::endl;
        }
    }

private:
    const std::vector<std::vector<double>>& portfolios_;
};

class Calculator {
public:
    Calculator(const std::vector<double>& values)
        : values_(values)
    {
    }
    double calculateTotal() const {
        return std::accumulate(values_.begin(), values_.end(), 0.0);
    }
    double calculateMean() const {
        if (values_.empty()) {
            return 0.0;
        }
        return calculateTotal() / values_.size();
    }

private:
    const std::vector<double>& values_;
};

int main() {
    std::vector<std::vector<double>> portfolios = {
        {10.0, 20.0, 30.0},
        {40.0, 50.0},
        {60.0, 70.0, 80.0, 90.0}
    };
    PortfolioAnalyzer analyzer(portfolios);
    analyzer.analyzePortfolios();
    return 0;
}
