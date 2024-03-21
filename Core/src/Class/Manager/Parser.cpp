#include "../../../Class/Manager.hpp"

namespace CoreModule {
    void Manager::Parser(int argc, char *argv[]) {
        if (argc != 2)
            throw CoreError("Usage: ./arcade path_to_graphical_library");
        this->loadLibraries(argv[1], GRAPHICAL);
        this->initialGraphicalLib = argv[1];
        if (this->libLoader->getDisplaySignature() != GRAPHICAL)
            throw CoreError("Invalid graphical library");
    }
}
