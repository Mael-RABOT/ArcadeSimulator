#include "../../Class/DLLoader.hpp"

namespace CoreModule {
    DLLoader::~DLLoader() {
        this->closeLibrary();
    }

    void DLLoader::openLibrary(const std::string &path, Signature libSignature) {
        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (lib == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        if (libSignature == GAME)
            this->gameLibrary = lib;
        else if (libSignature == GRAPHICAL)
            this->graphicalLibrary = lib;
        else
            throw CoreError("Invalid library signature");
    }

    void DLLoader::closeLibrary() {
        if (this->gameLibrary != nullptr) {
            dlclose(this->gameLibrary);
        }
        if (this->graphicalLibrary != nullptr) {
            dlclose(this->graphicalLibrary);
        }
    }

    IGameModule* DLLoader::getGameEntryPoint() {
        IGameModule* (*gameEntryPoint)() = (IGameModule* (*)())dlsym(this->gameLibrary, "entryPoint");
        if (gameEntryPoint == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        return gameEntryPoint();
    }

    Signature DLLoader::getGameSignature() {
        Signature (*gameGetSignature)() = (Signature (*)())dlsym(this->gameLibrary, "getSignature");
        if (gameGetSignature == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        return gameGetSignature();
    }

    IDisplayModule* DLLoader::getDisplayEntryPoint() {
        IDisplayModule* (*displayEntryPoint)() = (IDisplayModule* (*)())dlsym(this->graphicalLibrary, "entryPoint");
        if (displayEntryPoint == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        return displayEntryPoint();
    }

    Signature DLLoader::getDisplaySignature() {
        Signature (*displayGetSignature)() = (Signature (*)())dlsym(this->graphicalLibrary, "getSignature");
        if (displayGetSignature == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        return displayGetSignature();
    }
}
