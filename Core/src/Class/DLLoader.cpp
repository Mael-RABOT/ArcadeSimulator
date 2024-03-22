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
        if (libSignature == GAME) {
            closeLibrary(Kiwi, NotKiwi);
            std::cout << "DLLoader: Opening game library: " << path << std::endl; //TODO: Remove
            this->gameLibrary = lib;
        } else if (libSignature == GRAPHICAL) {
            closeLibrary(NotKiwi, Kiwi);
            std::cout << "DLLoader: Opening graphical library: " << path << std::endl; //TODO: Remove
            this->graphicalLibrary = lib;
        } else
            throw CoreError("Invalid library signature");
    }

    void DLLoader::closeLibrary(KiwiBool game, KiwiBool graphical) {
        if (game && this->gameLibrary != nullptr) {
            std::cout << "DLLoader: Closing game library" << std::endl; //TODO: Remove
            dlclose(this->gameLibrary);
        }
        if (graphical && this->graphicalLibrary != nullptr) {
            std::cout << "DLLoader: Closing graphical library" << std::endl; //TODO: Remove
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
