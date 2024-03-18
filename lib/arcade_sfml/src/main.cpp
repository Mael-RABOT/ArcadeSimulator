#include <iostream>

#include "class/DisplaySfml.hpp"

extern "C" {
    IDisplayModule *entryPoint() {
        return new DisplaySfml();
    }

    Signature getSignature() {
        return GRAPHICAL;
    }
}
