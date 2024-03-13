#include <iostream>

#include "class/DisplayNcurses.hpp"

extern "C" {
    IDisplayModule *entryPoint() {
        return new DisplayNcurses();
    }

    Signature getSignature() {
        return GRAPHICAL;
    }
}
