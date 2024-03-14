#include <iostream>

#include "../Class/Manager.hpp"

void kiwi();

int main(int argc, char *argv[]) {
    CoreModule::Manager manager;
    try {
        manager.initLibSelectors();
        manager.Parser(argc, argv);
        manager.loadLibraries("./lib/arcade_menu.so", Signature::GAME);
        manager.mainLoop();
    } catch (CoreModule::CoreError const &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
    kiwi();
    return 0;
}
