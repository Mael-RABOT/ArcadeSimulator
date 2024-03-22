#include "../../Class/DLLoader.hpp"

namespace CoreModule {
    DLLoader::DLLoader() {
        gameLibrary = nullptr;
        displayLibrary = nullptr;
        gameModule = nullptr;
        displayModule = nullptr;
    }

    DLLoader::~DLLoader() {
        this->close(Signature::GAME);
        this->close(Signature::GRAPHICAL);
    }

    void DLLoader::open(const std::string &path, Signature libSignature) {
        if (access(path.c_str(), F_OK) == -1) {
            throw CoreError("Error: file does not exist");
        }

        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!lib) {
            throw CoreError(std::string("Error: ") + dlerror());
        }

        Signature (*getSignature)() = (Signature (*)())dlsym(lib, "getSignature");
        if (!getSignature) {
            dlclose(lib);
            throw CoreError(std::string("Error: ") + dlerror());
        }

        if (getSignature() != libSignature) {
            dlclose(lib);
            throw CoreError("Error: invalid library signature");
        }

        if (libSignature == GAME) {
            gameEntryPoint = (IGameModule *(*)())dlsym(lib, "entryPoint");
            if (!gameEntryPoint) {
                dlclose(lib);
                throw CoreError(std::string("Error: ") + dlerror());
            }
            gameLibrary = lib;
            gameModule = gameEntryPoint();
        } else {
            displayEntryPoint = (IDisplayModule *(*)())dlsym(lib, "entryPoint");
            if (!displayEntryPoint) {
                dlclose(lib);
                throw CoreError(std::string("Error: ") + dlerror());
            }
            displayLibrary = lib;
            displayModule = displayEntryPoint();
        }
    }

    void DLLoader::close(Signature libSignature) {
        if (libSignature == GAME) {
            if (gameLibrary) {
                delete gameModule;
                gameModule = nullptr;

                dlclose(gameLibrary);
                gameLibrary = nullptr;
            }
        } else {
            if (displayLibrary) {
                delete displayModule;
                displayModule = nullptr;

                dlclose(displayLibrary);
                displayLibrary = nullptr;
            }
        }
    }

    Signature DLLoader::getSignature(const std::string &path) {
        if (access(path.c_str(), F_OK) == -1) {
            throw CoreError("Error: file does not exist");
        }

        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!lib) {
            throw CoreError(std::string("Error: ") + dlerror());
        }

        Signature (*getSignature)() = (Signature (*)())dlsym(lib, "getSignature");
        if (!getSignature) {
            dlclose(lib);
            throw CoreError(std::string("Error: ") + dlerror());
        }
        Signature signature = getSignature();
        dlclose(lib);
        return signature;
    }

    KiwiBool DLLoader::checkStatus() {
        return  static_cast<KiwiBool>(gameLibrary && displayLibrary);
    }

    void DLLoader::loadDefault(std::string defaultGraphical) {
        this->close(Signature::GAME);
        this->close(Signature::GRAPHICAL);
        this->open("./lib/arcade_menu.so", Signature::GAME);
        this->open(defaultGraphical, Signature::GRAPHICAL);
    }
}
