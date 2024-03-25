#include "../../../Class/Manager.hpp"

namespace CoreModule {
    Manager::Manager() {
        this->loader = new DLLoader();
        start = std::chrono::system_clock::now();
        username = "";
        isMenu = NotKiwi;
    }

    Manager::~Manager() { delete this->loader; }

    std::string Manager::Parser(int argc, char **argv) {
        if (argc != 2) {
            throw CoreError("Error: invalid number of arguments");
        }
        std::string path = argv[1];
        if (path.size() < 3 || path.substr(path.size() - 3) != ".so") {
            throw CoreError("Error: invalid library path");
        }
        Signature signature = this->loader->getSignature(path);
        if (signature != Signature::GRAPHICAL)
            throw CoreError("Error: invalid library signature");
        this->initialGraphicalLib = path;
        return path;
    }
}
