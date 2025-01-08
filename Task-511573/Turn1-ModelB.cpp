#include <iostream>
#include <string>
#ifdef USE_UTF8
#define STRING_TYPE std::string
#define STRING_LITERAL(s) s
#else
#define STRING_TYPE char*
#define STRING_LITERAL(s) s"\0"

typedef unsigned char uint8_t;

std::string utf8_to_ascii(const char* utf8_str) {
    std::string ascii_str;
    for (uint8_t ch : reinterpret_cast<const uint8_t*>(utf8_str)) {
        if (ch <= 0x7F) {
            ascii_str.push_back(ch);
        } else {
            // Handle invalid UTF-8 sequences for demonstration purposes
            ascii_str.push_back('?');
        }
    }
    return ascii_str;
}

STRING_TYPE convert_to_selected_encoding(const STRING_TYPE utf8_str) {
    return utf8_to_ascii(utf8_str).c_str();
}
#endif

void print_string(const STRING_TYPE str) {
#ifdef USE_UTF8
    std::cout << str << std::endl;
#else
    std::cout << str << std::endl;
#endif
}

int main() {
    const STRING_TYPE hello = STRING_LITERAL("Hello");
    const STRING_TYPE world = STRING_LITERAL("🌍World");

    print_string(hello);
    print_string(world);

#ifndef USE_UTF8
    const STRING_TYPE converted_world = convert_to_selected_encoding(world);
    print_string(converted_world);
#endif

    return 0;
}
