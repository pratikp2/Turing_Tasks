#include <iostream>

int main() {
    for (int i = 0; i < 1000000; ++i) {
        int* ptr = new int[1000];
        for (int j = 0; j < 1000; ++j) {
            ptr[j] = j;
        }
        delete[] ptr;
    }
    std::cout << "Program completed successfully!" << std::endl;
    return 0;
}
