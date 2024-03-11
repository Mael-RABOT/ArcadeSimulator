#include <string>
#include <dlfcn.h>

#include "Error/Error.hpp"

namespace Core {
    class Manager {
        private:
            void *graphicalLibrary;
            void *gameLibrary;

        public:
            Manager();
            ~Manager();
            void loadGraphicalLibrary(std::string const &path);
            void loadGameLibrary(std::string const &path);

            void Parser(int argc, char *argv[]);
    };
}
