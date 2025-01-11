#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <set>

struct Customer {
    int id;
    float purchasingBehavior; // e.g., score / amount spent
};

std::map<std::string, std::set<int>> segmentCustomers(const std::vector<Customer>& train) {
    std::map<std::string, std::set<int>> segments;
    
    // A simple segmentation logic based on purchasing behavior
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
    // Example dataset of customers
    std::vector<Customer> dataset = {
        {1, 20.5}, {2, 150.0}, {3, 80.3}, {4, 220.1},
        {5, 49.9}, {6, 300.0}, {7, 102.2}, {8, 25.0},
        {9, 10.0}, {10, 75.0}, {11, 500.0}, {12, 100.1}
    };
    
    // Shuffle dataset to ensure randomness
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dataset.begin(), dataset.end(), g);

    int k = 4; // Number of folds
    std::cout << "Performing " << k << "-fold cross-validation\n\n";
    kFoldCrossValidation(dataset, k);
    
    return 0;
}
