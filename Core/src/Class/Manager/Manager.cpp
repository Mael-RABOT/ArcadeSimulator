#include "../../../Class/Manager.hpp"

namespace CoreModule {
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

    KiwiBool Manager::checkSignature(const std::string &path, Signature const expectedSignature) {
        void *lib = DLLoader::openLibrary(path);
        Signature (*getSignature)() = (Signature (*)())dlsym(lib, "getSignature");
        if (getSignature == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        return (getSignature() == expectedSignature) ? Kiwi : NotKiwi;
    }

    Signature Manager::getLibSignature(const std::string &path) {
        void *lib = DLLoader::openLibrary(path);
        Signature (*getSignature)() = (Signature (*)())dlsym(lib, "getSignature");
        if (getSignature == nullptr) {
            throw CoreError(std::string(dlerror()));
        }
        Signature signature = getSignature();
        DLLoader::closeLibrary(lib);
        return signature;
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
