#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define a struct to represent a trade order
struct Order {
    double price;
    int quantity;
    bool isBuy;
};

// Function to perform binning on the price data
void binData(const vector<Order>& orders, vector<vector<Order>>& binned_orders, double bin_size) {
    double min_price = *min_element(orders.begin(), orders.end(), [](const Order& o1, const Order& o2) { return o1.price < o2.price; }).price;
    double max_price = *max_element(orders.begin(), orders.end(), [](const Order& o1, const Order& o2) { return o1.price < o2.price; }).price;
    int num_bins = static_cast<int>((max_price - min_price) / bin_size) + 1;

    binned_orders.assign(num_bins, vector<Order>());

    for (const Order& order : orders) {
        int bin_index = static_cast<int>((order.price - min_price) / bin_size);
        binned_orders[bin_index].push_back(order);
    }
}

// Function to find matching orders after binning
void findMatchingOrders(const vector<vector<Order>>& binned_buy_orders, const vector<vector<Order>>& binned_sell_orders, vector<pair<Order, Order>>& matches) {
    for (size_t bin_index = 0; bin_index < binned_buy_orders.size(); ++bin_index) {
        const vector<Order>& buy_orders_in_bin = binned_buy_orders[bin_index];
        const vector<Order>& sell_orders_in_bin = binned_sell_orders[bin_index];

        for (const Order& buy_order : buy_orders_in_bin) {
            for (const Order& sell_order : sell_orders_in_bin) {
                if (buy_order.price == sell_order.price && buy_order.quantity > 0 && sell_order.quantity > 0) {
                    matches.push_back({buy_order, sell_order});
                    buy_order.quantity -= min(buy_order.quantity, sell_order.quantity);
                    sell_order.quantity -= min(buy_order.quantity, sell_order.quantity);
                }
            }
        }
    }
}

int main() {
    // Generate some dummy trade order data
    vector<Order> buy_orders = {
        {100.0, 100}, {100.5, 50}, {99.0, 75}, {101.0, 20}, {102.0, 30}, {98.0, 60}, {100.0, 80},
        {100.3, 40}, {99.8, 90}, {100.2, 35}
    };

    vector<Order> sell_orders = {
        {100.2, 35}, {100.5, 60}, {101.0, 25}, {99.8, 85}, {100.0, 70}, {98.0, 40}, {100.8, 50},
        {100.3, 45}, {99.0, 65}, {102.0, 20}
    };

    // Choose an appropriate bin size based on your data distribution
    double bin_size = 0.5;

    vector<vector<Order>> binned_buy_orders;
    vector<vector<Order>> binned_sell_orders;

    binData(buy_orders, binned_buy_orders, bin_size);
    binData(sell_orders, binned_sell_orders, bin_size);

    vector<pair<Order, Order>> matches;

    findMatchingOrders(binned_buy_orders, binned_sell_orders, matches);

    cout << "Matched Orders:" << endl;
    for (const auto& match : matches) {
        cout << "Buy Order: Price=" << match.first.price << ", Quantity=" << match.first.quantity << endl;
        cout << "Sell Order: Price=" << match.second.price << ", Quantity=" << match.second.quantity << endl;
        cout << "------------------" << endl;
    }

    return 0;
}
