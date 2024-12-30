#include <iostream>
using namespace std;
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    const int* begin = arr;  // Pointer constant to the beginning of the array
    const int* end = begin + 5;  // Pointer constant to the end of the array

    // Array slicing using pointer constants
    const int* middle = begin + 2;  // Slicing to start from the 3rd element
    cout << "Original array: ";
    for (const int* p = begin; p != end; ++p) {
        cout << *p << " ";
    }
    cout << endl;
    cout << "Sliced array: ";
    for (const int* p = middle; p != end; ++p) {
        cout << *p << " ";
    }
    cout << endl;
    return 0;
}
