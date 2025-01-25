// financial_calculator.cpp
#include <iostream>
#pragma once

namespace FinancialConstants {
    // Tax rates
    constexpr double STANDARD_TAX_RATE = 0.15;
    constexpr double REDUCED_TAX_RATE = 0.05;
    constexpr double CAPITAL_GAINS_TAX_RATE = 0.10;

    // Tax thresholds
    constexpr double INCOME_TAX_THRESHOLD = 20000.0;
    constexpr double CAPITAL_GAINS_THRESHOLD = 10000.0;

    // Other constants
    constexpr int MAX_TRANSACTIONS_PER_DAY = 100;
    constexpr double INTEREST_RATE = 0.025;
}

namespace FinancialAnalytics {
    double calculateIncomeTax(double income) {
        if (income <= FinancialConstants::INCOME_TAX_THRESHOLD) {
            return 0;
        }
        double taxableIncome = income - FinancialConstants::INCOME_TAX_THRESHOLD;
        return taxableIncome * FinancialConstants::STANDARD_TAX_RATE;
    }

    double calculateCapitalGainsTax(double gains) {
        if (gains <= FinancialConstants::CAPITAL_GAINS_THRESHOLD) {
            return 0;
        }
        double taxableGains = gains - FinancialConstants::CAPITAL_GAINS_THRESHOLD;
        return taxableGains * FinancialConstants::CAPITAL_GAINS_TAX_RATE;
    }
}

int main() {
    double income = 30000.0;
    double capitalGains = 15000.0;

    double incomeTax = FinancialAnalytics::calculateIncomeTax(income);
    double capitalGainsTax = FinancialAnalytics::calculateCapitalGainsTax(capitalGains);

    std::cout << "Income Tax: $" << incomeTax << std::endl;
    std::cout << "Capital Gains Tax: $" << capitalGainsTax << std::endl;

    return 0;
}
