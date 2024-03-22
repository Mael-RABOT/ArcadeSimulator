#pragma once

#include <string>
#include <dlfcn.h>
#include <iostream>
#include <dirent.h>
#include <chrono>
#include <sstream>
#include <cstdlib>

#include "Type.hpp"
#include "DLLoader.hpp"
#include "IGameModule.hpp"
#include "IDisplayModule.hpp"
#include "ArcadeException.hpp"

namespace CoreModule {
    class Manager {
        private:
            std::chrono::time_point<std::chrono::system_clock> start;
            std::string initialGraphicalLib;

            void HandleLoadInstruction(std::string instruction);
            void HandleTextInstruction(std::string instruction);

        public:
            DLLoader *loader;
            Manager();
            ~Manager();

            std::string Parser(int argc, char *argv[]);
            void MainLoop();

            KiwiBool HandleEvent(std::chrono::seconds elapsed_seconds);
            void HandleInstruction();
            void HandleEntities();
    };
}
