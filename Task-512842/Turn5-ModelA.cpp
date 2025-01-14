#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <vector>

// Logging macro to log actions with a timestamp
#define LOG_ACTION(action)                                      \
    {                                                          \
        auto now = std::chrono::system_clock::now();          \
        std::time_t now_c = std::chrono::system_clock::to_time_t(now); \
        std::cout << "[LOG][" << std::ctime(&now_c) << "] "   \
                  << action << std::endl;                     \
    }

// Error handling macro
#define HANDLE_ERROR(errorMsg)                                 \
    {                                                          \
        std::cout << errorMsg << std::endl;                   \
        LOG_ACTION("Error: " + std::string(errorMsg));        \
    }

// Action structure
struct Action {
    std::string name;
    void (*function)(); // Pointer to the action function
};

// Forward declarations of action functions
void viewStockPrices();
void buyStock();
void sellStock();

// Action registry
std::vector<Action> actions;

// Macro to add a new action
#define ADD_ACTION(name, func) actions.push_back({name, func})

// Function to display available actions
void displayActions() {
    std::cout << "Select an action:\n";
    for (size_t i = 0; i < actions.size(); ++i) {
        std::cout << i + 1 << ": " << actions[i].name << "\n";
    }
    std::cout << "Enter your choice: ";
}

int main() {
    // Register default actions
    ADD_ACTION("View Stock Prices", viewStockPrices);
    ADD_ACTION("Buy Stock", buyStock);
    ADD_ACTION("Sell Stock", sellStock);
    ADD_ACTION("Exit", []() { 
        LOG_ACTION("User exited the application."); 
        std::cout << "Exiting the application.\n"; 
        exit(0); 
    });

    int action;

    while (true) {
        displayActions();
        std::cin >> action;

        if (action < 1 || action > static_cast<int>(actions.size())) {
            HANDLE_ERROR("Invalid action. Please try again.");
            continue;
        }

        // Log and execute the selected action
        LOG_ACTION("User selected action: " + actions[action - 1].name);
        actions[action - 1].function();
    }

    return 0;
}

void viewStockPrices() {
    std::cout << "Viewing current stock prices...\n";
    // Simulated stock prices
    std::map<std::string, double> stocks = {
        {"AAPL", 150.12},
        {"GOOGL", 2800.75},
        {"AMZN", 3400.00}
    };
    
    for (const auto& stock : stocks) {
        std::cout << stock.first << ": $" << stock.second << std::endl;
    }
}

void buyStock() {
    std::string stockSymbol;
    int quantity;
    
    std::cout << "Enter the stock symbol you want to buy: ";
    std::cin >> stockSymbol;
    std::cout << "Enter the quantity you want to buy: ";
    std::cin >> quantity;
    
    // Simplified buy operation
    std::cout << "Buying " << quantity << " shares of " << stockSymbol << "...\n";
}

void sellStock() {
    std::string stockSymbol;
    int quantity;
    
    std::cout << "Enter the stock symbol you want to sell: ";
    std::cin >> stockSymbol;
    std::cout << "Enter the quantity you want to sell: ";
    std::cin >> quantity;
    
    // Simplified sell operation
    std::cout << "Selling " << quantity << " shares of " << stockSymbol << "...\n";
}
