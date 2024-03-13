#pragma once

#include <string>
#include <dlfcn.h>

#include "Core.hpp"
#include "DLLoader.hpp"

namespace CoreModule {
    class Manager {
        private:
            void *graphicalLibrary;
            void *gameLibrary;
            Core *core;

        public:
            Manager();
            ~Manager();
            void loadGraphicalLibrary(std::string const &path);
            void loadGameLibrary(std::string const &path);

            void Parser(int argc, char *argv[]);
    };
}
