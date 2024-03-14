#include "../../../Class/Manager.hpp"

namespace CoreModule {
    Manager::Manager() {
        this->libLoader = new DLLoader();
        this->isRunning = Kiwi;
    }

    Manager::~Manager() { delete this->libLoader; }

    Signature Manager::getLibSignature(const std::string &path) {
        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (lib == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        Signature (*getSignature)() = (Signature (*)())dlsym(lib, "getSignature");
        if (getSignature == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        Signature signature = getSignature();
        dlclose(lib);
        return signature;
    }

    void Manager::loadLibraries(const std::string &path, Signature libSignature) {
        this->libLoader->openLibrary(path, libSignature);
        if (libSignature == GAME) {
            this->gameModule = this->libLoader->getGameEntryPoint();
        } else if (libSignature == GRAPHICAL) {
            this->displayModule = this->libLoader->getDisplayEntryPoint();
        }
    }

    void Manager::initLibSelectors() {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir ("./lib")) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                std::string filename = ent->d_name;
                if (filename.substr(filename.find_last_of(".") + 1) == "so") {
                    std::string path = "./lib/" + filename;
                    Signature signature = getLibSignature(path);
                    if (signature == GAME) {
                        gamesList.push_back(path);
                    } else if (signature == GRAPHICAL) {
                        graphicalList.push_back(path);
                    }
                }
            }
            closedir (dir);
        } else {
            throw CoreError("Could not open directory ./lib");
        }
    }
}
