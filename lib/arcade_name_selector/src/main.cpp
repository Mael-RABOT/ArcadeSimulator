#include <iostream>

#include "class/GameNameSelector.hpp"

extern "C" {
    IGameModule *entryPoint() {
        return new GameNameSelector();
    }

    Signature getSignature() {
        return GAME;
    }
}
