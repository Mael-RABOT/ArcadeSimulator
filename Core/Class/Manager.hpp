#pragma once

#include <string>
#include <dlfcn.h>
#include <iostream>
#include <dirent.h>

#include "Type.hpp"

#include "DLLoader.hpp"

namespace CoreModule {
    class Manager {
        private:
            void *graphicalLibrary;
            void *gameLibrary;
            std::vector<std::string> gamesList;
            std::vector<std::string> graphicalList;

        public:
            Manager();
            ~Manager();
            void loadGraphicalLibrary(std::string const &path);
            void loadGameLibrary(std::string const &path);

            void Parser(int argc, char *argv[]);
            KiwiBool checkSignature(std::string const &path, Signature const expectedSignature);
            Signature getLibSignature(std::string const &path);

            void initLibSelectors();
    };
}
