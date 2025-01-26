#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

// Simple in-memory database representation
class Database {
public:
    void insertCustomer(int id, const string& name) {
        customers[id] = name;
    }

    void insertOrder(int customerId, int orderId, const string& status) {
        auto& customerOrders = orders[customerId];
        customerOrders[orderId] = status;
    }

    string queryCustomer(int id) {
        auto it = customers.find(id);
        if (it == customers.end()) {
            return "Customer not found.";
        }
        return "Customer ID: " + to_string(id) + ", Name: " + it->second;
    }

    string queryOrders(int customerId) {
        auto it = orders.find(customerId);
        if (it == orders.end()) {
            return "Customer not found.";
        }
        string result = "Customer ID: " + to_string(customerId) + "\nOrders:\n";
        for (const auto& [orderId, status] : it->second) {
            result += "Order ID: " + to_string(orderId) + ", Status: " + status + "\n";
        }
        return result;
    }

private:
    unordered_map<int, string> customers;
    unordered_map<int, unordered_map<int, string>> orders;
};

int main() {
    Database db;

    // Sample data insertion
    db.insertCustomer(1, "Alice");
    db.insertCustomer(2, "Bob");
    db.insertOrder(1, 101, "Shipped");
    db.insertOrder(1, 102, "Pending");
    db.insertOrder(2, 103, "Delivered");

    string query;
    while (getline(cin, query)) {
        if (query.empty()) {
            break;
        }

        int level = 0;
        string queryType;
        int id = 0;

        // Simple parsing of the query string
        size_t pos = query.find(' ');
        if (pos != string::npos) {
            queryType = query.substr(0, pos);
            query = query.substr(pos + 1);
            pos = query.find(' ');
            if (pos != string::npos) {
                id = stoi(query.substr(0, pos));
                query = query.substr(pos + 1);
            }
        }

        string result;
        switch (level) {
            case 0:  // Customer-level queries
                if (queryType == "QUERY_CUSTOMER") {
                    result = db.queryCustomer(id);
                } 
                else if (queryType == "QUERY_ORDERS") {
                    result = db.queryOrders(id);
                } 
                else {
                    result = "Invalid query type.";
                }
                break;
            default:
                result = "Invalid query level.";
        }

        cout << result << endl;
    }

    return 0;
}
