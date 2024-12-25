#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

template <typename T>
std::vector<T> convertToVector(const std::basic_string<T>& str) {
    return std::vector<T>(str.begin(), str.end());
}

int main() {
    std::string utf8Str = "Hello, 世界"; // UTF-8 encoded string
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(utf8Str);
    
    // Convert to vector
    auto vec1 = convertToVector(utf8Str);
    auto vec2 = convertToVector(wideStr);

    // Output sizes
    std::cout << "UTF-8 size: " << vec1.size() << "\n";
    std::wcout << L"Wide string size: " << vec2.size() << L"\n";

    return 0;
}
