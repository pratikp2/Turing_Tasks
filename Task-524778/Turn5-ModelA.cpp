#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

struct Purchase {
    std::string productCategory;
    std::string date; // Using string for simplicity
};

class Customer {
public:
    std::string name;
    std::string region;
    std::string loyaltyTier; // Customer's loyalty tier
    std::vector<Purchase> purchases; // List of purchases

    Customer(const std::string& name, const std::string& region, const std::string& loyaltyTier)
        : name(name), region(region), loyaltyTier(loyaltyTier) {}
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB; // Mock database
    int nextId;

public:
    CustomerManagementSystem() : nextId(1) {}

    void addCustomer(const std::string& name, const std::string& region, const std::string& loyaltyTier) {
        customerDB[nextId++] = {name, region, loyaltyTier};
        std::cout << "Customer added with ID: " << nextId - 1 << std::endl;
    }

    void addPurchase(int customerId, const std::string& productCategory, const std::string& date) {
        if (customerDB.find(customerId) != customerDB.end()) {
            customerDB[customerId].purchases.push_back({productCategory, date});
            std::cout << "Purchase added for Customer ID: " << customerId << std::endl;
        } else {
            std::cout << "Customer not found with ID: " << customerId << std::endl;
        }
    }

    void performComplexQuery(const std::string& region, const std::string& productCategory, 
                             const std::string& startDate, const std::string& endDate) {
        std::cout << "Retrieving customers from Region: " << region 
                  << ", Product Category: " << productCategory 
                  << ", Date Range: " << startDate << " to " << endDate << "\n";

        for (const auto& entry : customerDB) {
            const Customer& customer = entry.second;
            if (customer.region == region) {
                if (isProductEligible(customer.loyaltyTier, productCategory)) {
                    processPurchases(entry.first, productCategory, startDate, endDate);
                }
            }
        }
    }

private:
    bool isProductEligible(const std::string& loyaltyTier, const std::string& productCategory) {
        switch (getTierCategory(loyaltyTier)) {
            case 1: return productCategory == "Basic";      // Silver
            case 2: return productCategory == "Basic" || productCategory == "Mid"; // Gold
            case 3: return true;                             // Platinum (any category)
            default: return false;
        }
    }

    int getTierCategory(const std::string& loyaltyTier) {
        if (loyaltyTier == "Silver") return 1;
        if (loyaltyTier == "Gold") return 2;
        if (loyaltyTier == "Platinum") return 3;
        return 0; // Unknown tier
    }

    void processPurchases(int customerId, const std::string& productCategory, 
                          const std::string& startDate, const std::string& endDate) {
        auto& customer = customerDB[customerId];
        for (const auto& purchase : customer.purchases) {
            if (purchase.productCategory == productCategory && isDateInRange(purchase.date, startDate, endDate)) {
                std::cout << "Customer ID: " << customerId << ", Name: " << customer.name 
                          << ", Purchase Date: " << purchase.date << "\n";
            }
        }
    }

    bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& endDate) {
        return date >= startDate && date <= endDate; // Simple date range check
    }
};

void displayMenu() {
    std::cout << "\n--- Customer Management System ---\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. Add Purchase\n";
    std::cout << "3. Query Customers\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void handleUserChoice(CustomerManagementSystem& cms, int choice) {
    switch (choice) {
        case 1: {
            std::string name, region, loyaltyTier;
            std::cout << "Enter Customer Name: ";
            std::cin >> name;
            std::cout << "Enter Region: ";
            std::cin >> region;
            std::cout << "Enter Loyalty Tier (Silver/Gold/Platinum): ";
            std::cin >> loyaltyTier;
            cms.addCustomer(name, region, loyaltyTier);
            break;
        }
        case 2: {
            int customerId;
            std::string productCategory, date;
            std::cout << "Enter Customer ID: ";
            std::cin >> customerId;
            std::cout << "Enter Product Category: ";
            std::cin >> productCategory;
            std::cout << "Enter Purchase Date (YYYY-MM-DD): ";
            std::cin >> date;
            cms.addPurchase(customerId, productCategory, date);
            break;
        }
        case 3: {
            std::string region, productCategory, startDate, endDate;
            std::cout << "Enter Region: ";
            std::cin >> region;
            std::cout << "Enter Product Category: ";
            std::cin >> productCategory;
            std::cout << "Enter Start Date (YYYY-MM-DD): ";
            std::cin >> startDate;
            std::cout << "Enter End Date (YYYY-MM-DD): ";
            std::cin >> endDate;
            cms.performComplexQuery(region, productCategory, startDate, endDate);
            break;
        }
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

int main() {
    CustomerManagementSystem cms;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        handleUserChoice(cms, choice);
    } while (choice != 4);

    return 0;
}
