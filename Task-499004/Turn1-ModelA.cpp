#include <iostream>
#include <cstring>
#include <ctime>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

class ShoppingCart {
private:
    char productNames[MAX_PRODUCTS][MAX_NAME_LENGTH];
    int productCount;

public:
    ShoppingCart() : productCount(0) {}

    void addProduct(const char* productName) {
        if (productCount < MAX_PRODUCTS) {
            strcpy(productNames[productCount], productName);
            productCount++;
        } else {
            std::cout << "Shopping cart is full!" << std::endl;
        }
    }

    void showProducts() const {
        std::cout << "Products in the cart:" << std::endl;
        for (int i = 0; i < productCount; ++i) {
            std::cout << productNames[i] << " (Length: " << strlen(productNames[i]) << ")" << std::endl;
        }
    }
};

int main() {
    ShoppingCart cart;

    // Simulate adding products
    const char* products[] = {"Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig", "Grape", "Honeydew"};
    
    clock_t start, end;
    start = clock();

    for (int i = 0; i < 8; ++i) {
        cart.addProduct(products[i]);
    }

    end = clock();
    double loadTime = double(end - start) / CLOCKS_PER_SEC;

    cart.showProducts();
    std::cout << "Load time for adding products: " << loadTime << " seconds" << std::endl;

    return 0;
}
