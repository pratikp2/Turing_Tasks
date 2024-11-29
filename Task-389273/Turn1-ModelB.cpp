#include <systemc.h>
#include "top.h"

int sc_main(int argc, char* argv[]) {
    top tb{"tb"};
    sc_start();
    return 0;
}
