#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

// Generic string copy function using templates
template <typename T>
void copyString(T* dest, const T* src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

int main() {
    const char* charSrc = "Hello, World!";
    char charDest[100];

    size_t charSrcLen = strlen(charSrc);

    // Using traditional strcpy for C strings
    cout << "Using traditional strcpy:" << endl;
    strcpy(charDest, charSrc);
    cout << "C string copied: " << charDest << endl;

    // Using generic string copy function for C strings
    cout << "\nUsing generic copyString for C strings:" << endl;
    copyString(charDest, charSrc, charSrcLen + 1); // +1 for null terminator
    cout << "C string copied with template: " << charDest << endl;

    const string strSrc = "Hello, C++ World!";
    string strDest;
    
    // Generic copy function can't be directly used for std::string
    // But we can demonstrate the value of templates in generic string handling functions

    cout << "\nUsing std::string for more modern approach:" << endl;
    strDest = strSrc;
    cout << "std::string copied: " << strDest << endl;
    return 0;
}
