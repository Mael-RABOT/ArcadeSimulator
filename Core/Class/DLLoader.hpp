#pragma once

#include <string>
#include <unordered_map>
#include <dlfcn.h>
#include <typeinfo>

#include "../Class/Error/Error.hpp"
#include "Type.hpp"
#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

namespace CoreModule {
    class DLLoader {
        private:
            void *gameLibrary;
            void *graphicalLibrary;

            IGameModule* (*gameEntryPoint)();
            Signature (*gameGetSignature)();

            IDisplayModule* (*displayEntryPoint)();
            Signature (*displayGetSignature)();

        public:
            DLLoader() = default;
            ~DLLoader();

            void openLibrary(const std::string &path, Signature libSignature);
            void closeLibrary();

            IGameModule* getGameEntryPoint();
            Signature getGameSignature();

            IDisplayModule* getDisplayEntryPoint();
            Signature getDisplaySignature();
    };
}
