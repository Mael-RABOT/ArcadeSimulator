#include <iostream>

#include "class/GameMenu.hpp"

extern "C" {
    IGameModule *entryPoint() {
        return new GameMenu();
    }

    Signature getSignature() {
        return GAME;
    }
}
