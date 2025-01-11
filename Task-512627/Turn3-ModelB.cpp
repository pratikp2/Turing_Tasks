#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <set>

struct Customer {
    int id;
    float purchasingBehavior;
};

bool isValidCustomer(const Customer& customer) {
    // Assuming purchasingBehavior == 0 represents missing data
    return customer.purchasingBehavior > 0;
}

std::map<std::string, std::set<int>> segmentCustomers(const std::vector<Customer>& train) {
    std::map<std::string, std::set<int>> segments;

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

        // Filter out invalid customers with missing data
        auto filteredDataset = dataset | std::filter(isValidCustomer);

        for (int j = 0; j < filteredDataset.size(); ++j) {
            if (j >= i * foldSize && j < (i + 1) * foldSize) {
                test.push_back(filteredDataset[j]);
            } else {
                train.push_back(filteredDataset[j]);
            }
        }

        auto segments = segmentCustomers(train);

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
    // Example dataset with a few invalid records (purchasingBehavior == 0)
    std::vector<Customer> dataset = {
        {1, 20.5}, {2, 0.0}, {3, 80.3}, {4, 0.0}, {5, 49.9},
        {6, 300.0}, {7, 102.2}, {8, 25.0}, {9, 0.0}, {10, 75.0},
        {11, 500.0}, {12, 100.1}, {13, 0.0}, {14, 180.0}, {15, 120.0}
    };

    int k = 4;
    std::cout << "Performing " << k << "-fold cross-validation\n\n";
    kFoldCrossValidation(dataset, k);

    return 0;
}
