#include <iostream>
#include <string>

namespace FinancialConstants {
    // Defining global constants using constexpr
    constexpr double TAX_RATE = 0.15;         // 15% tax rate
    constexpr double DISCOUNT_RATE = 0.10;    // 10% discount rate
    constexpr double FREE_SHIPPING_THRESHOLD = 50.0; // Free shipping for orders over $50
}

// Function to calculate the total cost after tax
double calculateTotalWithTax(double amount) {
    return amount + (amount * FinancialConstants::TAX_RATE);
}

// Function to calculate the total cost after discount
double calculateTotalWithDiscount(double amount) {
    return amount - (amount * FinancialConstants::DISCOUNT_RATE);
}

// Function to determine if an order is eligible for free shipping
bool isEligibleForFreeShipping(double amount) {
    return amount >= FinancialConstants::FREE_SHIPPING_THRESHOLD;
}

int main() {
    double orderAmount = 60.0; // Example order amount

    // Calculate totals
    double totalAfterTax = calculateTotalWithTax(orderAmount);
    double totalAfterDiscount = calculateTotalWithDiscount(orderAmount);
    
    // Check for free shipping eligibility
    bool freeShipping = isEligibleForFreeShipping(orderAmount);

    // Output results
    std::cout << "Order Amount: $" << orderAmount << "\n";
    std::cout << "Total after Tax: $" << totalAfterTax << "\n";
    std::cout << "Total after Discount: $" << totalAfterDiscount << "\n";
    std::cout << "Eligible for Free Shipping: " << (freeShipping ? "Yes" : "No") << "\n";

    return 0;
}
