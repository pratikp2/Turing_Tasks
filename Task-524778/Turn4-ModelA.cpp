#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>

struct Purchase {
    std::string productCategory;
    std::string date; // Using string for simplicity
};

struct Customer {
    std::string name;
    std::string region;
    std::string loyaltyTier; // New loyalty tier
    std::vector<Purchase> purchases; // List of purchases
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB; // Mock database
    int nextId = 1;

public:
    void addCustomer(const std::string& name, const std::string& region, const std::string& loyaltyTier) {
        customerDB[nextId++] = {name, region, loyaltyTier, {}};
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

    void performComplexQuery(const std::string& region, const std::string& productCategory, const std::string& startDate, const std::string& endDate) {
        std::cout << "Retrieving customers from Region: " << region << ", Product Category: " << productCategory << ", Date Range: " << startDate << " to " << endDate << std::endl;

        for (const auto& entry : customerDB) {
            const Customer& customer = entry.second;
            if (customer.region == region) {
                switch (getTierCategory(customer.loyaltyTier)) {
                    case 1: // Silver
                        if (productCategory == "Basic") {
                            processPurchases(entry.first, productCategory, startDate, endDate);
                        }
                        break;
                    case 2: // Gold
                        if (productCategory == "Basic" || productCategory == "Mid") {
                            processPurchases(entry.first, productCategory, startDate, endDate);
                        }
                        break;
                    case 3: // Platinum
                        processPurchases(entry.first, productCategory, startDate, endDate);
                        break;
                    default:
                        std::cerr << "Unknown loyalty tier.\n";
                }
            }
        }
    }

private:
    int getTierCategory(const std::string& loyaltyTier) {
        if (loyaltyTier == "Silver") return 1;
        if (loyaltyTier == "Gold") return 2;
        if (loyaltyTier == "Platinum") return 3;
        return 0; // Unknown tier
    }

    void processPurchases(int customerId, const std::string& productCategory, const std::string& startDate, const std::string& endDate) {
        const Customer& customer = customerDB[customerId];
        for (const auto& purchase : customer.purchases) {
            if (purchase.productCategory == productCategory && isDateInRange(purchase.date, startDate, endDate)) {
                std::cout << "Customer ID: " << customerId << ", Name: " << customer.name << ", Purchase Date: " << purchase.date << std::endl;
            }
        }
    }

    bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& endDate) {
        return date >= startDate && date <= endDate;
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

int main() {
    CustomerManagementSystem cms;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

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
    } while (choice != 4);

    return 0;
}
