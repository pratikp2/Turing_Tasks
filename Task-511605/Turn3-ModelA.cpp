#include <iostream>
#include <locale>
#include <libintl.h>

#define _(STRING) gettext(STRING)

int main() {
    // Setting locale
    setlocale(LC_ALL, "");
    bindtextdomain("messages", "./locale");
    textdomain("messages");

    std::cout << _( "Welcome" ) << std::endl;
    std::cout << _( "Energy Usage" ) << ": 123.45 " << _( "Kilowatt-hours" ) << std::endl;

    return 0;
}
