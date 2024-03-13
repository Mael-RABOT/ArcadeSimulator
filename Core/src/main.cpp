#include <iostream>

#include "../Class/Manager.hpp"

int main(int argc, char *argv[]) {
    CoreModule::Manager manager;
    try {
        manager.Parser(argc, argv);
        manager.initLibSelectors();
    } catch (CoreModule::CoreError const &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
    return 0;
}
