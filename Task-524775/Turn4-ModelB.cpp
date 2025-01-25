#include <iostream>
#include <string>

namespace FinancialConstants {
    // Constants using constexpr
    constexpr double TAX_RATE = 0.15;
    constexpr double DISCOUNT_RATE = 0.10;
    constexpr double FREE_SHIPPING_THRESHOLD = 50.0;
}

enum class CalculationError {
    SUCCESS,
    INVALID_ORDER_AMOUNT, // Amount is negative or zero
    EXCESSIVE_TAX_RATE,   // Tax rate is set above 1.0
    EXCESSIVE_DISCOUNT_RATE, // Discount rate is set above 1.0
};

double calculateTotalWithTax(double amount) {
    if (amount <= 0.0) {
        return CalculationError::INVALID_ORDER_AMOUNT; // Return an error code
    }
    
    if (FinancialConstants::TAX_RATE > 1.0) {
        return CalculationError::EXCESSIVE_TAX_RATE;
    }

    return amount + (amount * FinancialConstants::TAX_RATE);
}

double calculateTotalWithDiscount(double amount) {
    if (amount <= 0.0) {
        return CalculationError::INVALID_ORDER_AMOUNT;
    }

    if (FinancialConstants::DISCOUNT_RATE > 1.0) {
        return CalculationError::EXCESSIVE_DISCOUNT_RATE;
    }

    return amount - (amount * FinancialConstants::DISCOUNT_RATE);
}

bool isEligibleForFreeShipping(double amount) {
    return amount >= FinancialConstants::FREE_SHIPPING_THRESHOLD;
}

int main() {
    double orderAmount = -10.0; // Invalid order amount for testing

    CalculationError taxResult = calculateTotalWithTax(orderAmount);
    CalculationError discountResult = calculateTotalWithDiscount(orderAmount);

    if (taxResult == CalculationError::SUCCESS) {
        double totalAfterTax = static_cast<double>(taxResult);
        std::cout << "Order Amount: $" << orderAmount << "\n";
        std::cout << "Total after Tax: $" << totalAfterTax << "\n";
    } else {
        std::cout << "Error: ";
        switch (taxResult) {
            case CalculationError::INVALID_ORDER_AMOUNT:
                std::cout << "Invalid order amount." << std::endl;
                break;
            case CalculationError::EXCESSIVE_TAX_RATE:
                std::cout << "Excessive tax rate." << std::endl;
                break;
            default:
                std::cout << "Unknown error." << std::endl;
        }
    }

    return 0;
}
