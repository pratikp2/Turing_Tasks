#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

struct Purchase {
    std::string productCategory;
    std::string date; // Using string for simplicity
};

struct Customer {
    std::string name;
    std::string region;
    std::vector<Purchase> purchases; // List of purchases
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB; // Mock database
    int nextId = 1;

public:
    void addCustomer(const std::string& name, const std::string& region) {
        customerDB[nextId++] = {name, region, {}};
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
                for (const auto& purchase : customer.purchases) {
                    if (purchase.productCategory == productCategory && isDateInRange(purchase.date, startDate, endDate)) {
                        std::cout << "Customer ID: " << entry.first << ", Name: " << customer.name << ", Purchase Date: " << purchase.date << std::endl;
                    }
                }
            }
        }
    }

private:
    bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& endDate) {
        // Here assume date is in "YYYY-MM-DD" format, so lexicographical comparison works for ranges.
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
                std::string name, region;
                std::cout << "Enter Customer Name: ";
                std::cin >> name;
                std::cout << "Enter Region: ";
                std::cin >> region;
                cms.addCustomer(name, region);
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
