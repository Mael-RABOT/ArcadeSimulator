#include "../../Class/DLLoader.hpp"

namespace CoreModule {
    DLLoader::DLLoader() {
        gameLibrary = nullptr;
        displayLibrary = nullptr;
        gameModule = nullptr;
        displayModule = nullptr;
        gameIndex = 0;
        displayIndex = 0;
        initList();
    }

    void DLLoader::initList() {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir ("./lib")) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                std::string filename = ent->d_name;
                if (filename.substr(filename.find_last_of(".") + 1) == "so") {
                    std::string path = "./lib/" + filename;
                    Signature signature = getSignature(path);
                    if (signature == GAME) {
                        gamesList.push_back(path);
                    } else if (signature == GRAPHICAL) {
                        displayList.push_back(path);
                    }
                }
            }
            closedir (dir);
        }
    }

    void DLLoader::nextGame() {
        if (gamesList.size() == 0) {
            throw CoreError("Error: no game library found");
        }
        gameIndex = (gameIndex + 1) % gamesList.size();
        this->close(Signature::GAME);
        this->open(gamesList[gameIndex], Signature::GAME);
        this->gameModule->getMap();
        this->gameModule->getEntities();
        this->displayModule->loadDicts(this->gameModule->getSpriteDict(), this->gameModule->getStaticScreen());
    }

    void DLLoader::nextDisplay() {
        if (displayList.size() == 0) {
            throw CoreError("Error: no display library found");
        }
        displayIndex = (displayIndex + 1) % displayList.size();
        this->close(Signature::GRAPHICAL);
        this->open(displayList[displayIndex], Signature::GRAPHICAL);
        this->displayModule->loadDicts(this->gameModule->getSpriteDict(), this->gameModule->getStaticScreen());
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
