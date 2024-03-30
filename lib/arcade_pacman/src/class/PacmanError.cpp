#include "PacmanError.hpp"

pacman::Error pacman::quickError(const Error::ErrorType_t type) {
    std::string message;
    switch (type) {
        case pacman::Error::MAP_NOT_FOUND:
            message = std::string("PACMAN : ERROR : assets/pacman_map.txt file not found.");
        break;
        case pacman::Error::MAP_CORRUPTED:
            message = std::string("PACMAN : ERROR : assets/pacman_map.txt file is corrupted.");
        break;
        case pacman::Error::MAP_UNINITIALIZED:
            message = std::string("PACMAN : ERROR : The map has not been initialized.");
        break;
        case pacman::Error::ENTITIES_UNINITIALIZED:
            message = std::string("PACMAN : ERROR : The entities has not been initialized.");
        break;
        case pacman::Error::FORBIDDEN_ACTION:
            message = std::string("PACMAN : ERROR : A forbidden action has been asked to an entity.");
        break;
        default:
            message = std::string("PACMAN : ERROR : Undifined error.");
    }
    pacman::Error err(message);
    return err;
}
