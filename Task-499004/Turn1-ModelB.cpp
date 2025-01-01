#include <iostream>
#include <cstring>

using namespace std;

int main() {
    const int maxLength = 100;
    char productName[maxLength];
    char* tempName = new char[maxLength];

    // Input a product name
    cout << "Enter the name of the product: ";
    cin.getline(productName, maxLength);

    // Copy the input string to another using strcpy
    strcpy(tempName, productName);

    // Display the length of the string using strlen
    cout << "Length of the product name '" << tempName << "' is: " << strlen(tempName) << endl;

    // Clean up
    delete[] tempName;
    tempName = nullptr;

    return 0;
}
