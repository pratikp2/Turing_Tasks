#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

struct Customer {
    std::string name;
    std::string email;
    std::string phone;
    std::vector<std::string> purchases;  // To hold purchase history
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB;
    int nextId = 1;

    // Simulation of complex database queries
    std::vector<Customer> getCustomersByCity(const std::string& city) const {
        // Replace this with actual database query logic
        std::vector<Customer> customers;
        for (const auto& entry : customerDB) {
            // Simple mock to select customers by city, not actually based on purchases
            if (entry.second.purchases.size() > 0) {
                customers.push_back(entry.second);
            }
        }
        return customers;
    }

public:
    // (Existing functions from before...)

    void performComplexRetrieval(int choice) {
        switch (choice) {
            case 6: {
                std::cout << "-- Retrieve Customer History by Spending: --" << std::endl;
                retrieveCustomerHistory();
                break;
            }
            case 7: {
                std::cout << "-- Get Customers by City: --" << std::endl;
                retrieveCustomersByCity();
                break;
            }
            default:
                std::cout << "Invalid choice for retrieval task." << std::endl;
        }
    }

private:
    void retrieveCustomerHistory() {
        int customerId;
        std::cout << "Enter Customer ID to retrieve purchase history: ";
        std::cin >> customerId;

        auto it = customerDB.find(customerId);
        if (it != customerDB.end()) {
            const Customer& customer = it->second;
            std::cout << "\nPurchase History for " << customer.name << ":\n";
            for (const auto& purchase : customer.purchases) {
                std::cout << "- " << purchase << std::endl;
            }
        } else {
            std::cout << "Customer not found with ID: " << customerId << std::endl;
        }
    }
    void retrieveCustomersByCity() {
        std::string city;
        std::cout << "Enter city to retrieve customers: ";
        std::cin >> city;

        auto customersByCity = getCustomersByCity(city);
        if (customersByCity.empty()) {
            std::cout << "No customers found in " << city << std::endl;
        } else {
            std::cout << "Customers in " << city << ":\n";
            for (const auto& customer : customersByCity) {
                std::cout << "\nCustomer ID: " << customer.name << ", Email: " << customer.email << std::endl;
            }
        }
    }
};

int main() {
   // (... Existing code...)

    do {
        std::cout << "-- Customer Management System --" << std::endl;
        std::cout << "1. Add Customer\n";
        // (... Existing choices...)
        std::cout << "6. Retrieve Customer Purchase History\n";
        std::cout << "7. Get Customers by City\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        cms.performComplexRetrieval(choice);

    } while (choice != 8);

    return 0;
}
