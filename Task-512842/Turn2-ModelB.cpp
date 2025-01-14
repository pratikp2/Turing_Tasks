#include <iostream>
#include <string>
#include <map>

enum class StockAction {
    VIEW_PRICES,
    BUY_STOCK,
    SELL_STOCK,
    EXIT
};

#define ACTION_VIEW_PRICES (static_cast<int>(StockAction::VIEW_PRICES))
#define ACTION_BUY_STOCK (static_cast<int>(StockAction::BUY_STOCK))
#define ACTION_SELL_STOCK (static_cast<int>(StockAction::SELL_STOCK))
#define ACTION_EXIT (static_cast<int>(StockAction::EXIT))

#define LOG_INFO(msg) std::cout << "INFO: " << msg << std::endl
#define LOG_ERROR(msg) std::cout << "ERROR: " << msg << std::endl

void viewStockPrices();
void buyStock();
void sellStock();

int main() {
    int action;
    
    while (true) {
        LOG_INFO("Select an action:");
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
                LOG_INFO("Exiting the application.");
                return 0;
            default:
                LOG_ERROR("Invalid action. Please try again.");
        }
    }

    return 0;
}

// Rest of the functions remain the same
