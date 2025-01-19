#include <iostream>
#include <map>
#include <string>
#include <chrono>

#include <random> // Added for random key generation

using namespace std;
using namespace std::chrono;

// Inline function for lookup in std::map
inline double lookupStockPrice(const map<string, double>& prices, const string& stock) {
    return prices.find(stock)->second;
}

// Non-inline function for lookup in std::map
double nonInlineLookupStockPrice(const map<string, double>& prices, const string& stock) {
    return prices.find(stock)->second;
}

// Inline function for lookup in std::unordered_map
inline double lookupStockPriceUnordered(const unordered_map<string, double>& prices, const string& stock) {
    return prices.find(stock)->second;
}

// Non-inline function for lookup in std::unordered_map
double nonInlineLookupStockPriceUnordered(const unordered_map<string, double>& prices, const string& stock) {
    return prices.find(stock)->second;
}

int main() {
    const int numStocks = 100000;
    const int numLookups = 1000000;
    random_device rd;
    mt19937 gen(rd());
    string stockSymbols[numStocks];
    
    // Generate random stock symbols and prices
    for (int i = 0; i < numStocks; ++i) {
        stringstream ss;
        ss << i << "_Company" << i % 26 + 'A';  // Generate symbols like 0_CompanyA, 1_CompanyB
        stockSymbols[i] = ss.str();
    }
    
    map<string, double> orderedPrices;
    unordered_map<string, double> unorderedPrices;
    
    for (int i = 0; i < numStocks; ++i) {
        double price = UniformRealDistribution<double>(0.0, 1000.0)(gen);
        orderedPrices[stockSymbols[i]] = price;
        unorderedPrices[stockSymbols[i]] = price;
    }
    auto start = steady_clock::now();
    
    // Use inline function for lookups on std::map
    for (int i = 0; i < numLookups; ++i) {
        int randomIndex = random_int_distribution<>(0, numStocks - 1)(gen);
        lookupStockPrice(orderedPrices, stockSymbols[randomIndex]);
    }
    auto end = steady_clock::now();
    double inlineMapLookupTime = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    start = steady_clock::now();
    
    // Use non-inline function for lookups on std::map
    for (int i = 0; i < numLookups; ++i) {
        int randomIndex = random_int_distribution<>(0, numStocks - 1)(gen);
        nonInlineLookupStockPrice(orderedPrices, stockSymbols[randomIndex]);
    }
    end = steady_clock::now();
    double nonInlineMapLookupTime = duration_cast<microseconds>(end - start).count() / 1000.0;

    // Repeat for unordered_map
    start = steady_clock::now();
    
    // Use inline function for lookups on std::unordered_map
    for (int i = 0; i < numLookups; ++i) {
        int randomIndex = random_int_distribution<>(0, numStocks - 1)(gen);
        lookupStockPriceUnordered(unorderedPrices, stockSymbols[randomIndex]);
    }
    end = steady_clock::now();
    double inlineUnorderedMapLookupTime = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    start = steady_clock::now();
    
    // Use non-inline function for lookups on std::unordered_map
    for (int i = 0; i < numLookups; ++i) {
        int randomIndex = random_int_distribution<>(0, numStocks - 1)(gen);
        nonInlineLookupStockPriceUnordered(unorderedPrices, stockSymbols[randomIndex]);
    }
    end = steady_clock::now();
    double nonInlineUnorderedMapLookupTime = duration_cast<microseconds>(end - start).count() / 1000.0;

    // Output the results
    cout << "Lookup times in milliseconds:" << endl;
    cout << "std::map (inline): " << inlineMapLookupTime << endl;
    cout << "std::map (non-inline): " << nonInlineMapLookupTime << endl;
    cout << "std::unordered_map (inline): " << inlineUnorderedMapLookupTime << endl;
    cout << "std::unordered_map (non-inline): " << nonInlineUnorderedMapLookupTime << endl;

    return 0;
}
