#ifndef PACMAN_ERROR
    #define PACMAN_ERROR
    
    #include <string>
    #include "ArcadeException.hpp"

namespace pacman {
    class Error : public ArcadeException {
        public:
            typedef enum ErrorType {
                UNKNOWN,
                MAP_NOT_FOUND,
                MAP_CORRUPTED,
                MAP_UNINITIALIZED,
                ENTITIES_UNINITIALIZED,
                FORBIDDEN_ACTION,
                ENTITY_CORRUPTED,
                GAME_CRASH
            } ErrorType_t;

            Error(const std::string &message) : ArcadeException(message) {};
    };

    Error quickError(const Error::ErrorType_t type);
}
#endif
