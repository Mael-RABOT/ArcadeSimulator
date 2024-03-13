#include "../../../Class/Manager.hpp"

namespace CoreModule {
    Manager::Manager() {
        this->graphicalLibrary = nullptr;
        this->gameLibrary = nullptr;
        this->core = new Core();
    }

    Manager::~Manager() {
        if (this->graphicalLibrary != nullptr) {
            dlclose(this->graphicalLibrary);
        }
        if (this->gameLibrary != nullptr) {
            dlclose(this->gameLibrary);
        }
        delete this->core;
    }

    void Manager::loadGraphicalLibrary(std::string const &path) {
        if (this->graphicalLibrary != nullptr) {
            DLLoader::closeLibrary(this->graphicalLibrary);
        }
        void *lib = DLLoader::openLibrary(path);
        if (lib == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        this->graphicalLibrary = lib;
    }

    void Manager::loadGameLibrary(std::string const &path) {
        if (this->gameLibrary != nullptr) {
            DLLoader::closeLibrary(this->gameLibrary);
        }
        void *lib = DLLoader::openLibrary(path);
        if (lib == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        this->gameLibrary = lib;
    }
}
