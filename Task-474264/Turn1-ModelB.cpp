#include <iostream>

// Version 1 of the library
inline namespace lib_v1 {
    int add(int a, int b) {
        std::cout << "Using lib_v1::add()\n";
        return a + b;
    }
}

// Version 2 of the library, introducing a change in the behavior of 'add'
inline namespace lib_v2 {
    int add(int a, int b) {
        std::cout << "Using lib_v2::add()\n";
        return a + b + 1;  // Different behavior
    }
}

namespace app {
    void use_library(const std::string& version) {
        if (version == "v1") {
            using namespace lib_v1;
            std::cout << "Result: " << add(10, 20) << std::endl;
        } else if (version == "v2") {
            using namespace lib_v2;
            std::cout << "Result: " << add(10, 20) << std::endl;
        } else {
            std::cout << "Invalid library version.\n";
        }
    }
}

int main() {
    app::use_library("v1");
    app::use_library("v2");
    return 0;
}
