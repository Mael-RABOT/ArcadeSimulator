#include "../../../Class/Manager.hpp"

namespace Core {
    void Manager::Parser(int argc, char *argv[]) {
        if (argc != 2) {
            throw CoreError("Usage: ./arcade path_to_graphical_library");
        }
        this->loadGraphicalLibrary(argv[1]);
    }
}
