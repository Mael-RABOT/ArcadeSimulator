#include <iostream>

#include "class/DisplaySdl.hpp"

extern "C" {
    IDisplayModule *entryPoint() {
        return new DisplaySdl();
    }

    Signature getSignature() {
        return GRAPHICAL;
    }
}
