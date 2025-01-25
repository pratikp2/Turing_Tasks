#include <iostream>
#include <string>

namespace FinancialConstants {
    // Global constants using constexpr
    constexpr double TAX_RATE = 0.15;         // 15% tax rate
    constexpr double DISCOUNT_RATE = 0.10;    // 10% discount rate
    constexpr double FREE_SHIPPING_THRESHOLD = 50.0; // Free shipping for orders over $50
}

// Enum class for order statuses
enum class OrderStatus {
    Pending,
    Processed,
    Shipped,
    Delivered,
    Cancelled
};

// Enum class for error codes
enum class ErrorCode {
    None,
    InvalidAmount,
    OutOfStock,
    PaymentFailed
};

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

// Function to process an order and return an error code
ErrorCode processOrder(double amount, OrderStatus& status) {
    if (amount <= 0) {
        status = OrderStatus::Cancelled; // Set order status to cancelled
        return ErrorCode::InvalidAmount; // Return error code
    }
    
    // Here you may add more logic to check stock, payment, etc.
    
    status = OrderStatus::Processed; // Set order status to processed
    return ErrorCode::None; // No error
}

int main() {
    double orderAmount = 60.0; // Example order amount
    OrderStatus orderStatus = OrderStatus::Pending; // Initial order status
    ErrorCode errorCode = processOrder(orderAmount, orderStatus);

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
    
    // Output order status and error code
    std::cout << "Order Status: " << static_cast<int>(orderStatus) << "\n";
    std::cout << "Error Code: " << static_cast<int>(errorCode) << "\n";
    
    return 0;
}
