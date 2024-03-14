#include "../../../Class/Manager.hpp"

namespace CoreModule {
    void Manager::Parser(int argc, char *argv[]) {
        if (argc != 2)
            throw CoreError("Usage: ./arcade path_to_graphical_library");
        this->libLoader->openLibrary(argv[1], GRAPHICAL);
        if (this->libLoader->getDisplaySignature() != GRAPHICAL)
            throw CoreError("Invalid graphical library");
    }
}
