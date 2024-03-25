#include <iostream>

#include "../Class/Manager.hpp"

void kiwi();

int main(int argc, char *argv[]) {
    CoreModule::Manager manager;
    try {
        std::string displayModule = manager.Parser(argc, argv);
        manager.loader->open(displayModule, Signature::GRAPHICAL);
        manager.loader->open("./lib/arcade_menu.so", Signature::GAME);
        if (!manager.loader->checkStatus()) {
            throw CoreModule::CoreError("Error: invalid library status");
        }
        if (manager.loader->gameModule == nullptr) return 14;
        manager.MainLoop();
    } catch (CoreModule::CoreError const &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
    kiwi();
    return 0;
}
