#pragma once

#include <string>
#include <dlfcn.h>
#include <iostream>
#include <dirent.h>

#include "Type.hpp"

#include "DLLoader.hpp"
#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

namespace CoreModule {
    class Manager {
        private:
            KiwiBool isRunning;
            DLLoader *libLoader;
            IGameModule *gameModule;
            IDisplayModule *displayModule;
            std::vector<std::string> gamesList;
            std::vector<std::string> graphicalList;

        public:
            Manager();
            ~Manager();
            void loadLibraries(std::string const &path, Signature libSignature);

            void Parser(int argc, char *argv[]);
            Signature getLibSignature(std::string const &path);

            void initLibSelectors();

            void mainLoop();
            KiwiBool handleEvent();
    };
}
