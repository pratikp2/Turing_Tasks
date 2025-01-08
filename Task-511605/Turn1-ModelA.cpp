#include <iostream>

// Language Definitions
#define LANGUAGE_EN 1
#define LANGUAGE_ES 2

// Language Constants
#if LANGUAGE == LANGUAGE_EN
    #define MSG_WELCOME "Welcome to the energy management software!"
    #define MSG_EXIT "Thank you for using our software. Goodbye!"
#elif LANGUAGE == LANGUAGE_ES
    #define MSG_WELCOME "¡Bienvenido al software de gestión de energía!"
    #define MSG_EXIT "Gracias por usar nuestro software. ¡Adiós!"
#endif

void displayMessages() {
    std::cout << MSG_WELCOME << std::endl;
    // ... other operations
    std::cout << MSG_EXIT << std::endl;
}

int main() {
    // Set the language (could be done based on user input)
    #define LANGUAGE LANGUAGE_EN // Change to LANGUAGE_ES for Spanish

    displayMessages();
    return 0;
}
