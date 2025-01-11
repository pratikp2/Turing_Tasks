#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <set>
#include <cmath> // For std::isnan
#include <thread>
#include <future>
#include <queue>

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

// Function to segment customers dynamically
void segmentCustomers(const std::vector<Customer>& customers, std::map<std::string, std::set<int>>& segments) {
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
// Function to process a single fold concurrently
void processFold(int i, const std::vector<Customer>& foldData, std::map<std::string, std::set<int>>& segments) {
    std::vector<Customer> train, test;

    // Partition fold data into train and test sets
    int foldSize = foldData.size() / 4;
    for (int j = 0; j < foldData.size(); ++j) {
        if (j >= i * foldSize && j < (i + 1) * foldSize) {
            test.push_back(foldData[j]);
        } else {
            train.push_back(foldData[j]);
        }
    }
 
    segmentCustomers(train, segments);
}

void kFoldCrossValidation(const std::vector<Customer>& dataset, int k) {
    
    for (int i = 0; i < k; ++i) {
        std::map<std::string, std::set<int>> segments;
        std::thread thread(processFold, i, dataset, std::ref(segments));
        threads.push_back(std::move(thread));
    }
    
    for (std::thread& thread : threads) {
        thread.join();
    }

    threads.clear();
}

int main() {
    // Example dataset
    std::vector<Customer> dataset = { ... };
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dataset.begin(), dataset.end(), g);

    auto validDataset = filterInvalidCustomers(dataset);

    int k = 4; // Number of folds
    std::cout << "Performing " << k << "-fold cross-validation\n\n";
    kFoldCrossValidation(validDataset, k);
    
    return 0;
}
