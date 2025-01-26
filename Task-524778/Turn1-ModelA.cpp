#include <iostream>
#include <unordered_map>
#include <string>

struct Customer {
    std::string name;
    std::string email;
    std::string phone;
};

class CustomerManagementSystem {
private:
    std::unordered_map<int, Customer> customerDB;
    int nextId = 1;

public:
    void addCustomer(const std::string& name, const std::string& email, const std::string& phone) {
        customerDB[nextId] = {name, email, phone};
        std::cout << "Customer added with ID: " << nextId++ << std::endl;
    }

    void retrieveCustomer(int id) {
        auto it = customerDB.find(id);
        if (it != customerDB.end()) {
            const Customer& customer = it->second;
            std::cout << "Customer ID: " << id << ", Name: " << customer.name << ", Email: " << customer.email << ", Phone: " << customer.phone << std::endl;
        } else {
            std::cout << "Customer not found with ID: " << id << std::endl;
        }
    }

    void updateCustomer(int id, const std::string& name, const std::string& email, const std::string& phone) {
        auto it = customerDB.find(id);
        if (it != customerDB.end()) {
            it->second = {name, email, phone};
            std::cout << "Customer updated with ID: " << id << std::endl;
        } else {
            std::cout << "Customer not found with ID: " << id << std::endl;
        }
    }

    void deleteCustomer(int id) {
        if (customerDB.erase(id)) {
            std::cout << "Customer deleted with ID: " << id << std::endl;
        } else {
            std::cout << "Customer not found with ID: " << id << std::endl;
        }
    }
};

int main() {
    CustomerManagementSystem cms;
    int choice;
    
    do {
        std::cout << "Customer Management System\n";
        std::cout << "1. Add Customer\n";
        std::cout << "2. Retrieve Customer\n";
        std::cout << "3. Update Customer\n";
        std::cout << "4. Delete Customer\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, email, phone;
                std::cout << "Enter Name: ";
                std::cin >> name;
                std::cout << "Enter Email: ";
                std::cin >> email;
                std::cout << "Enter Phone: ";
                std::cin >> phone;
                cms.addCustomer(name, email, phone);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter Customer ID: ";
                std::cin >> id;
                cms.retrieveCustomer(id);
                break;
            }
            case 3: {
                int id;
                std::string name, email, phone;
                std::cout << "Enter Customer ID: ";
                std::cin >> id;
                std::cout << "Enter New Name: ";
                std::cin >> name;
                std::cout << "Enter New Email: ";
                std::cin >> email;
                std::cout << "Enter New Phone: ";
                std::cin >> phone;
                cms.updateCustomer(id, name, email, phone);
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter Customer ID: ";
                std::cin >> id;
                cms.deleteCustomer(id);
                break;
            }
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
