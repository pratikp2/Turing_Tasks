#include <iostream>
#include <string>
#include <map>

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
                viewStockPrices();
                break;
            case ACTION_BUY_STOCK:
                buyStock();
                break;
            case ACTION_SELL_STOCK:
                sellStock();
                break;
            case ACTION_EXIT:
                std::cout << "Exiting the application.\n";
                return 0; // Exit the program
            default:
                std::cout << "Invalid action. Please try again.\n";
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
    // In real application, you would call a function to handle the transaction here.
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
    // In real application, you would call a function to handle the transaction here.
}
