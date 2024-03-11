#include "../../../Class/Manager.hpp"

namespace Core {
    Manager::Manager() {
        this->graphicalLibrary = nullptr;
        this->gameLibrary = nullptr;
    }

    Manager::~Manager() {
        if (this->graphicalLibrary != nullptr) {
            dlclose(this->graphicalLibrary);
        }
        if (this->gameLibrary != nullptr) {
            dlclose(this->gameLibrary);
        }
    }

    void Manager::loadGraphicalLibrary(std::string const &path) {
        if (this->graphicalLibrary != nullptr) {
            dlclose(this->graphicalLibrary);
        }
        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (lib == nullptr) {
            throw CoreError("Cannot open the graphical library: " + std::string(dlerror()));
        }
        this->graphicalLibrary = lib;
    }

    void Manager::loadGameLibrary(std::string const &path) {
        if (this->gameLibrary != nullptr) {
            dlclose(this->gameLibrary);
        }
        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (lib == nullptr) {
            throw CoreError("Cannot open the game library: " + std::string(dlerror()));
        }
        this->gameLibrary = lib;
    }
}
