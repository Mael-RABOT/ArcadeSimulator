#include "../../Class/DLLoader.hpp"

namespace CoreModule {
    void *DLLoader::openLibrary(const std::string &path) {
        void *handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            throw CoreError(dlerror());
        }
        return handle;
    }

    void *DLLoader::getSymbol(const std::string &symbol) {
        void *ptr = dlsym(nullptr, symbol.c_str());
        if (!ptr) {
            throw CoreError(dlerror());
        }
        return ptr;
    }

    void DLLoader::closeLibrary(void *handle) {
        if (!handle)
            throw CoreError("Cannot close a null handle");
        dlclose(handle);
    }
}
