#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

enum class LoyaltyTier {
    Bronze,
    Silver,
    Gold
};

struct Purchase {
    std::string productCategory;
    std::string date; // Using string for simplicity
};

struct Customer {
    std::string name;
    std::string region;
    LoyaltyTier loyaltyTier;
    std::vector<Purchase> purchases; // List of purchases
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB;
    int nextId = 1;

    // Other functions... (Remained the same)

public:
    void performComplexQuery(const std::string& region, const LoyaltyTier& loyaltyTier, const std::string& productCategory, const std::string& startDate, const std::string& endDate) {
        std::cout << "Retrieving customers from Region: " << region << ", Loyalty Tier: " << getLoyaltyTierName(loyaltyTier) << ", Product Category: " << productCategory << ", Date Range: " << startDate << " to " << endDate << std::endl;

        for (const auto& entry : customerDB) {
            const Customer& customer = entry.second;
            if (customer.region == region && customer.loyaltyTier == loyaltyTier) {
                for (const auto& purchase : customer.purchases) {
                    if (purchase.productCategory == productCategory && isDateInRange(purchase.date, startDate, endDate)) {
                        std::cout << "Customer ID: " << entry.first << ", Name: " << customer.name << ", Purchase Date: " << purchase.date << std::endl;
                    }
                }
            }
        }
    }

    std::string getLoyaltyTierName(LoyaltyTier tier) {
        switch (tier) {
            case LoyaltyTier::Bronze:
                return "Bronze";
            case LoyaltyTier::Silver:
                return "Silver";
            case LoyaltyTier::Gold:
                return "Gold";
        }
        return "Unknown";
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
                // (... Existing code ...)
                break;
            }
            case 2: {
                // (... Existing code ...)
                break;
            }
            case 3: {
                std::string region;
                LoyaltyTier loyaltyTier;
                std::string productCategory, startDate, endDate;

                std::cout << "Enter Region: ";
                std::cin >> region;

                std::cout << "Enter Loyalty Tier (Bronze/Silver/Gold): ";
                std::string tierInput;
                std::cin >> tierInput;
                if (tierInput == "Bronze") {
                    loyaltyTier = LoyaltyTier::Bronze;
                } else if (tierInput == "Silver") {
                    loyaltyTier = LoyaltyTier::Silver;
                } else if (tierInput == "Gold") {
                    loyaltyTier = LoyaltyTier::Gold;
                } else {
                    std::cout << "Invalid loyalty tier. Returning to main menu." << std::endl;
                    continue;
                }

                std::cout << "Enter Product Category: ";
                std::cin >> productCategory;
                std::cout << "Enter Start Date (YYYY-MM-DD): ";
                std::cin >> startDate;
                std::cout << "Enter End Date (YYYY-MM-DD): ";
                std::cin >> endDate;
                cms.performComplexQuery(region, loyaltyTier, productCategory, startDate, endDate);
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
