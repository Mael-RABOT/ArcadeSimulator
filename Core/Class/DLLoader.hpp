#pragma once

#include <string>
#include <unordered_map>
#include <dlfcn.h>
#include <typeinfo>

#include "../Class/Error/Error.hpp"

namespace CoreModule {
    class DLLoader {
        public:
            DLLoader() = delete;
            ~DLLoader() = delete;

            static void *openLibrary(const std::string &path);
            static void *getSymbol(const std::string &symbol);
            static void closeLibrary(void *handle);
    };
}
