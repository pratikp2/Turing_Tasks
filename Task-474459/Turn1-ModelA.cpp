#include <iostream>
#include <cstring>
#include <type_traits>

template <typename T>
void myStrCopy(T* dest, const T* src, size_t maxSize) {
    static_assert(std::is_same<T, char>::value || std::is_same<T, wchar_t>::value,
                  "myStrCopy only supports char and wchar_t types.");
    
    size_t i = 0;
    while (i < maxSize - 1 && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0'; // Null-terminate the destination string
}

int main() {
    char source[] = "Hello, World!";
    char destination[50];

    myStrCopy(destination, source, sizeof(destination));
    std::cout << "Copied string: " << destination << std::endl;

    wchar_t wSource[] = L"Hello, Wide World!";
    wchar_t wDestination[50];

    myStrCopy(wDestination, wSource, sizeof(wDestination) / sizeof(wchar_t));
    std::wcout << L"Copied wide string: " << wDestination << std::endl;

    return 0;
}
