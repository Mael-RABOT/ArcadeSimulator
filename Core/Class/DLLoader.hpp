#pragma once

#include <string>
#include <unordered_map>
#include <dlfcn.h>
#include <typeinfo>
#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include <dirent.h>

#include "../Class/Error/Error.hpp"
#include "Type.hpp"
#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

namespace CoreModule {
    class DLLoader {
        private:
            void *gameLibrary;
            void *displayLibrary;

            IGameModule* (*gameEntryPoint)();
            Signature (*gameGetSignature)();

            IDisplayModule* (*displayEntryPoint)();
            Signature (*displayGetSignature)();

            std::vector<std::string> gamesList;
            std::vector<std::string> displayList;
            std::size_t gameIndex;
            std::size_t displayIndex;

        public:
            IGameModule *gameModule;
            IDisplayModule *displayModule;

            DLLoader();
            ~DLLoader();

            void open(const std::string &path, Signature libSignature);
            void close(Signature libSignature);

            Signature getSignature(const std::string &path);
            KiwiBool checkStatus();

            void nextGame();
            void nextDisplay();

            void loadDefault(std::string defaultGraphical);
            void initList();
    };
}
