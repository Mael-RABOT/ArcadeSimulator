#include <iostream>

#include "class/GamePacman.hpp"

extern "C" {
    IGameModule *entryPoint() {
        return new GamePacman();
    }

    Signature getSignature() {
        return GAME;
    }
}
