#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <set>
#include <cmath> // For std::isnan

struct Customer {
    int id;
    float purchasingBehavior; // e.g., score / amount spent
};

// Function to check if the customer data is valid
bool isValidCustomer(const Customer& customer) {
    return !std::isnan(customer.purchasingBehavior) && customer.purchasingBehavior >= 0;
}

// Function to filter out invalid customers
std::vector<Customer> filterInvalidCustomers(const std::vector<Customer>& dataset) {
    std::vector<Customer> validCustomers;
    validCustomers.reserve(dataset.size()); // Reserve memory for efficiency
    for (const auto& customer : dataset) {
        if (isValidCustomer(customer)) {
            validCustomers.push_back(customer);
        }
    }
    return validCustomers;
}

std::map<std::string, std::set<int>> segmentCustomers(const std::vector<Customer>& train) {
    std::map<std::string, std::set<int>> segments;
    
    // Simple segmentation based on purchasing behavior
    for (const auto& customer : train) {
        if (customer.purchasingBehavior < 50.0) {
            segments["Low Value"].insert(customer.id);
        } else if (customer.purchasingBehavior < 200.0) {
            segments["Mid Value"].insert(customer.id);
        } else {
            segments["High Value"].insert(customer.id);
        }
    }

    return segments;
}

void kFoldCrossValidation(const std::vector<Customer>& dataset, int k) {
    int foldSize = dataset.size() / k;
    
    for (int i = 0; i < k; ++i) {
        std::vector<Customer> train;
        std::vector<Customer> test;

        for (int j = 0; j < dataset.size(); ++j) {
            if (j >= i * foldSize && j < (i + 1) * foldSize) {
                test.push_back(dataset[j]);
            } else {
                train.push_back(dataset[j]);
            }
        }

        // Perform segmentation on training data
        auto segments = segmentCustomers(train);

        // Logging results
        std::cout << "Fold " << i + 1 << ":\n";
        std::cout << "Test set contains " << test.size() << " customers.\n";
        std::cout << "Segments:\n";
        for (const auto& segment : segments) {
            std::cout << segment.first << ": ";
            for (int id : segment.second) {
                std::cout << id << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

int main() {
    // Example dataset of customers, some with invalid purchasing behavior
    std::vector<Customer> dataset = {
        {1, 20.5}, {2, 150.0}, {3, 80.3}, {4, NAN}, // Customer 4 has invalid data
        {5, 49.9}, {6, 300.0}, {7, -10.0}, {8, 25.0}, // Customer 7 has invalid data
        {9, 10.0}, {10, 75.0}, {11, 500.0}, {12, 100.1}
    };
    
    // Shuffle dataset to ensure randomness
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dataset.begin(), dataset.end(), g);

    // Filter out invalid customers
    auto validDataset = filterInvalidCustomers(dataset);

    int k = 4; // Number of folds
    std::cout << "Performing " << k << "-fold cross-validation\n\n";
    kFoldCrossValidation(validDataset, k);
    
    return 0;
}
