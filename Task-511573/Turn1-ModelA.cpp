#include <iostream>
#include <string>

#define ENCODING_UTF8  // Uncomment this to use UTF-8 encoding
// #define ENCODING_UTF16  // Uncomment this to use UTF-16 encoding

void printString(const std::string& str) {
#ifdef ENCODING_UTF8
    std::cout << "UTF-8: " << str << std::endl;
#elif defined(ENCODING_UTF16)
    std::wstring wstr(str.begin(), str.end()); // simplistic conversion
    std::wcout << L"UTF-16: " << wstr << std::endl;
#else
    std::cout << "Unknown Encoding" << std::endl;
#endif
}

int main() {
    std::string sampleString = "Hello, World!";
    printString(sampleString);
    return 0;
}
