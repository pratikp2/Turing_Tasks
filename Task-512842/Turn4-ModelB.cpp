#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>

// Logging macro to log actions with a timestamp
#define LOG_ACTION(action)                                      \
    {                                                          \
        auto now = std::chrono::system_clock::now();          \
        std::time_t now_c = std::chrono::system_clock::to_time_t(now); \
        std::cout << "[LOG][" << std::ctime(&now_c) << "] "   \
                  << action << std::endl;                     \
    }

// Error handling macro to log and display invalid inputs
#define HANDLE_INVALID_INPUT(message)                         \
    {                                                          \
        auto now = std::chrono::system_clock::now();          \
        std::time_t now_c = std::chrono::system_clock::to_time_t(now); \
        std::cout << "[ERROR][" << std::ctime(&now_c) << "] "  \
                  << message << std::endl;                     \
        std::cout << "Invalid action. Please try again.\n";    \
    }

// Define action macros
#define ACTION_VIEW_PRICES 1
#define ACTION_BUY_STOCK 2
#define ACTION_SELL_STOCK 3
#define ACTION_EXIT 4

// Function prototypes
void viewStockPrices();
void buyStock();
void sellStock();

int main() {
    int action;
    
    while (true) {
        std::cout << "Select an action:\n";
        std::cout << ACTION_VIEW_PRICES << ": View Stock Prices\n";
        std::cout << ACTION_BUY_STOCK << ": Buy Stock\n";
        std::cout << ACTION_SELL_STOCK << ": Sell Stock\n";
        std::cout << ACTION_EXIT << ": Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> action;

        switch (action) {
            case ACTION_VIEW_PRICES:
                LOG_ACTION("User viewed stock prices.");
                viewStockPrices();
                break;
            case ACTION_BUY_STOCK:
                LOG_ACTION("User initiated buying stock.");
                buyStock();
                break;
            case ACTION_SELL_STOCK:
                LOG_ACTION("User initiated selling stock.");
                sellStock();
                break;
            case ACTION_EXIT:
                LOG_ACTION("User exited the application.");
                std::cout << "Exiting the application.\n";
                return 0; // Exit the program
            default:
                HANDLE_INVALID_INPUT("Unknown action selected.");
                break;
        }
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
