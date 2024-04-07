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
            std::string username;

            void HandleLoadInstruction(std::string instruction);
            void HandleTextInstruction(std::string instruction);

            std::string current_game;

        public:
            DLLoader *loader;
            Manager();
            ~Manager();

            std::string Parser(int argc, char *argv[]);
            void MainLoop();

            KiwiBool HandleEvent(std::size_t elapsed_seconds);
            void HandleInstruction();
            void HandleEntities();
    };
}
