#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

struct Customer {
    int id;
    float purchasingBehavior;
};

void groupCustomersIntoSegments(const std::vector<Customer>& customers, std::map<std::string, std::set<int>>& segments) {
    // Dynamic segmentation based on purchasing behavior
    for (const auto& customer : customers) {
        if (customer.purchasingBehavior < 50.0) {
            segments["Low Value"].insert(customer.id);
        } else if (customer.purchasingBehavior < 200.0) {
            segments["Mid Value"].insert(customer.id);
        } else {
            segments["High Value"].insert(customer.id);
        }
    }
}

int main() {
    // Example dataset
    std::vector<Customer> customers = {
        {1, 120.0}, {2, 40.0}, {3, 70.5}, {4, 250.0},
        {5, 300.0}, {6, 10.0}, {7, 180.2}, {8, 60.3}
    };

    // dynamically created map of segments, that automatically refrees with the new chunks.
    std::map<std::string, std::set<int>> segments;
    
    // Group customers into segments
    groupCustomersIntoSegments(customers, segments);
    
    // Log the segments
    std::cout << "Segments:\n";
    for (const auto& segment : segments) {
        std::cout << segment.first << ": ";
        for (int id : segment.second) {
            std::cout << id << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
