#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

struct Customer {
    std::string name;
    std::string email;
    std::string phone;
    std::vector<std::string> purchaseHistory; // List of items purchased
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB;
    int nextId = 1;

public:
    void addCustomer(const std::string& name, const std::string& email, const std::string& phone) {
        customerDB[nextId] = {name, email, phone, {}};
        std::cout << "Customer added with ID: " << nextId++ << std::endl;
    }

    void queryCustomers(int criteriaType, const std::string& criteriaValue) {
        switch (criteriaType) {
            case 1: // By ID
                int id = std::stoi(criteriaValue);
                retrieveCustomerById(id);
                break;
            case 2: // By Email Domain
                retrieveCustomersByEmailDomain(criteriaValue);
                break;
            case 3: // By Purchase History
                retrieveCustomersByPurchaseHistory(criteriaValue);
                break;
            default:
                std::cout << "Invalid criteria type!\n";
                break;
        }
    }
    
    void retrieveCustomerById(int id) {
        auto it = customerDB.find(id);
        if (it != customerDB.end()) {
            const Customer& customer = it->second;
            std::cout << "Customer ID: " << id << ", Name: " << customer.name << ", Email: " << customer.email << ", Phone: " << customer.phone << std::endl;
        } else {
            std::cout << "Customer not found with ID: " << id << std::endl;
        }
    }

    void retrieveCustomersByEmailDomain(const std::string& domain) {
        std::cout << "Customers with email domain " << domain << ":\n";
        for (const auto& pair : customerDB) {
            const Customer& customer = pair.second;
            if (customer.email.find(domain) != std::string::npos) {
                std::cout << "ID: " << pair.first << ", Name: " << customer.name << "\n";
            }
        }
    }

    void retrieveCustomersByPurchaseHistory(const std::string& item) {
        std::cout << "Customers who purchased " << item << ":\n";
        for (const auto& pair : customerDB) {
            const Customer& customer = pair.second;
            if (std::find(customer.purchaseHistory.begin(), customer.purchaseHistory.end(), item) != customer.purchaseHistory.end()) {
                std::cout << "ID: " << pair.first << ", Name: " << customer.name << "\n";
            }
        }
    }

    void recordPurchase(int id, const std::string& item) {
        auto it = customerDB.find(id);
        if (it != customerDB.end()) {
            it->second.purchaseHistory.push_back(item);
            std::cout << "Recorded purchase for customer ID " << id << ": " << item << std::endl;
        } else {
            std::cout << "Customer not found with ID: " << id << std::endl;
        }
    }
};

int main() {
    CustomerManagementSystem cms;
    cms.addCustomer("Alice", "alice@example.com", "123-456-7890");
    cms.addCustomer("Bob", "bob@example.com", "123-456-7891");
    cms.addCustomer("Charlie", "charlie@example.com", "123-456-7892");
    
    cms.recordPurchase(1, "Laptop");
    cms.recordPurchase(2, "Phone");
    cms.recordPurchase(1, "Mouse");

    int choice;
    do {
        std::cout << "\nQuery Customers\n";
        std::cout << "1. By Customer ID\n";
        std::cout << "2. By Email Domain\n";
        std::cout << "3. By Purchase History\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::cout << "Enter Customer ID: ";
                std::cin >> id;
                cms.queryCustomers(1, std::to_string(id));
                break;
            }
            case 2: {
                std::string domain;
                std::cout << "Enter Email Domain (e.g., '@example.com'): ";
                std::cin >> domain;
                cms.queryCustomers(2, domain);
                break;
            }
            case 3: {
                std::string item;
                std::cout << "Enter Item Purchased: ";
                std::cin >> item;
                cms.queryCustomers(3, item);
                break;
            }
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
