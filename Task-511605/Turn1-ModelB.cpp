#include <iostream>

// Define constants for different languages
#define LANGUAGE_ENGLISH
//#define LANGUAGE_SPANISH

// Language strings defined using #define constants
#ifdef LANGUAGE_ENGLISH
#define STR_WELCOME "Welcome"
#define STR_ENERGY_USAGE "Energy Usage"
#define STR_KILOWATTHOURS "Kilowatt-hours"
#elseif defined(LANGUAGE_SPANISH)
#define STR_WELCOME "Bienvenido"
#define STR_ENERGY_USAGE "Uso de Energía"
#define STR_KILOWATTHOURS "Kilovatios-hora"
#endif

int main() {
    std::cout << STR_WELCOME << std::endl;
    std::cout << "Current " << STR_ENERGY_USAGE << ": 123.45 " << STR_KILOWATTHOURS << std::endl;

    return 0;
}
