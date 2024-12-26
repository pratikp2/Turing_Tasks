#include <iostream>
void duplicateArrayUsingPointers(int* arr, int n) {
    int *modifiedArray = new int[2*n];
    int* readPtr = arr;
    int* writePtr = modifiedArray;
    for (int i = 0; i < n; i++) {
        *writePtr = *readPtr;
        writePtr++;
        *writePtr = *readPtr;
        writePtr++;
        readPtr++;
    }
 

    //Display the modified array
    std::cout << "Modified Array: ";
    for (writePtr = modifiedArray; writePtr < modifiedArray + 2*n; writePtr++){
        std::cout << *writePtr << " ";
    }
    std::cout << std::endl;
    delete[] modifiedArray;
}
int main() {
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    int* arr = new int[n];
    std::cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    duplicateArrayUsingPointers(arr, n);
    delete[] arr;

    return 0;
}
