#include <iostream>
#include <libintl.h>

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("myproject", "locale");
    textdomain("myproject");

    std::cout << _("Welcome") << std::endl;
    std::cout << _("Current Energy Usage: 123.45 Kilowatt-hours") << std::endl;

    return 0;
}
setlocale(LC_ALL, "");
bindtextdomain("myproject", "locale");
textdomain("myproject");

// Switch to Spanish language
bindtextdomain("myproject", "locale/es");
textdomain("myproject");

std::cout << _("Welcome") << std::endl;
