#include <iostream>

#include "../Class/Manager.hpp"

int main(int argc, char *argv[]) {
    Core::Manager manager;
    try {
        manager.Parser(argc, argv);
    } catch (Core::CoreError const &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
    return 0;
}
