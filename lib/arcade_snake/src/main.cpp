#include <iostream>

#include "class/GameSnake.hpp"

extern "C" {
    IGameModule *entryPoint() {
        return new GameSnake();
    }

    Signature getSignature() {
        return GAME;
    }
}
