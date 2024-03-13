#include "../../../Class/Manager.hpp"

namespace CoreModule {
    void Manager::Parser(int argc, char *argv[]) {if (argc != 2) {throw CoreError("Usage: ./arcade path_to_graphical_library");}this->loadGraphicalLibrary(argv[1]); if (this->checkSignature(argv[1], GRAPHICAL)) ; else {throw CoreError("Invalid graphical library");}}
}
