#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <cstring>

#define ACTION_VIEW_PRICES 1
#define ACTION_BUY_STOCK 2
#define ACTION_SELL_STOCK 3
#define ACTION_EXIT 4

#define LOG_ACTION(action) std::cout << getCurrentTimestamp() << ": ACT: " << #action << std::endl;

std::string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return buffer;
}

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
                LOG_ACTION(ACTION_VIEW_PRICES);
                viewStockPrices();
                break;
            case ACTION_BUY_STOCK:
                LOG_ACTION(ACTION_BUY_STOCK);
                buyStock();
                break;
            case ACTION_SELL_STOCK:
                LOG_ACTION(ACTION_SELL_STOCK);
                sellStock();
                break;
            case ACTION_EXIT:
                LOG_ACTION(ACTION_EXIT);
                std::cout << "Exiting the application.\n";
                return 0;
            default:
                std::cout << "Invalid action. Please try again.\n";
        }
    }

    return 0;
}
//rest of the functions...
