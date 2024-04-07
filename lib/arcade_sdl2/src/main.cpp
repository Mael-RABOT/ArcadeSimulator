#include <iostream>

#include "class/DisplaySdl2.hpp"

extern "C" {
    IDisplayModule *entryPoint() {
        return new DisplaySdl();
    }

    Signature getSignature() {
        return GRAPHICAL;
    }
}
