#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <array>

// Logging macro to log actions with a timestamp
#define LOG_ACTION(action, funcName)                                     \
    {                                                                    \
        auto now = std::chrono::system_clock::now();                    \
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);  \
        std::cout << "[LOG][" << std::ctime(&now_c) << "] "              \
                  << action << " - Executing " << funcName << std::endl; \
    }

// Error handling macro
#define HANDLE_ERROR(errorMsg)                                    \
    {                                                            \
        std::cout << errorMsg << std::endl;                       \
        LOG_ACTION("Error: " + std::string(errorMsg), "");        \
    }

// Define action macros and associated function pointers
#define DECLARE_ACTION(actionName, actionCode, func) \
    static const struct Action { int code = actionCode; const char* name = #actionName; void (*handler)(void) = func; } actionName

#define REGISTER_ACTIONS(...) { __VA_ARGS__ }

// Define the actions and their corresponding handlers
DECLARE_ACTION(viewPrices, ACTION_VIEW_PRICES, viewStockPrices);
DECLARE_ACTION(buyStock, ACTION_BUY_STOCK, buyStock);
DECLARE_ACTION(sellStock, ACTION_SELL_STOCK, sellStock);
DECLARE_ACTION(exitApp, ACTION_EXIT, []() { std::cout << "Exiting the application.\n"; });

// Array to store all registered actions
const std::array<const struct Action, 4> allActions = REGISTER_ACTIONS(viewPrices, buyStock, sellStock, exitApp);

// Function to handle actions dynamically
void handleAction(int action) {
    for (const auto& actionDesc : allActions) {
        if (actionDesc.code == action) {
            LOG_ACTION(actionDesc.name, actionDesc.handler ? actionDesc.handler->__func__ : "");
            actionDesc.handler();
            return;
        }
    }
    HANDLE_ERROR("Invalid action. Please try again.");
}

int main() {
    int action;

    while (true) {
        std::cout << "Select an action:\n";
        for (const auto& actionDesc : allActions) {
            std::cout << actionDesc.code << ": " << actionDesc.name << "\n";
        }
        std::cout << "Enter your choice: ";
        std::cin >> action;

        handleAction(action);

        if (action == ACTION_EXIT) {
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
