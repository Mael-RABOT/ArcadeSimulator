#include "GamePacman.hpp"

void GamePacman::handleInput(std::size_t deltaTime, Input input) {
    if (this->map.empty())
        throw pacman::createError(pacman::Error::MAP_UNINITIALIZED);
}

void GamePacman::update(std::size_t deltaTime) {
    if (this->map.empty())
        throw pacman::createError(pacman::Error::MAP_UNINITIALIZED);
}

std::vector<std::string> GamePacman::getInstruction() {
    
}

EntityDescription GamePacman::getEntities() {
    return this->entityDescriptor;
}

Map GamePacman::getMap() {
    if (!this->map.empty())
        return this->map;
    ifstream mapFile;
    mapFile.open ("assets/pacman_map.txt");
    if (!mapFile.is_open()) {
        throw pacman::createError(pacman::Error::MAP_NOT_FOUND);
    }
    std::string line;
    while(std::getline(mapFile, line)) {
        if (!this->map.empty() && this->map.end().size() != line.length() - 1) {
            throw pacman::createError(pacman::Error::MAP_CORRUPTED);
        }
        std::vector<EntityType> mapLine;
        for (std::string::iterator c = line.begin(); c != line.end(); c++) {
            if (c == '#') {
                mapLine.push_back(WALL);
            } else if (c == ' ') {
                mapLine.push_back(UNDEFINED);
            } else if (c != '\n') {
                throw pacman::createError(pacman::Error::MAP_CORRUPTED);
            }
        }
        this->map.push_back(mapLine);
    }
    mapFile.close();
    return this->map;
}

std::map<EntityType, std::string> GamePacman::getSpriteDict() {
    std::map<EntityType, std::string> dict = {
        {WALL, std::string("wall.png")}
    }
    return dict;
}

std::map<StaticScreen, std::string> GamePacman::getStaticScreen() {
    std::map<EntityType, std::string> dict = {
    }
    return dict;
}

namespace pacman {
    const char *Error::what(void) const noexcept {
        switch (this->_type) {
            case pacman::Error::MAP_NOT_FOUND:
                return "PACMAN : ERROR : assets/pacman_map.txt file not found.";
            case pacman::Error::MAP_CORRUPTED:
                return "PACMAN : ERROR : assets/pacman_map.txt file is corrupted.";
            case pacman::Error::MAP_UNINITIALIZED:
                return "PACMAN : ERROR : the map has not been initialized.";
            default:
                return "PACMAN : ERROR : Undifined error";
        }
    }

    void Error::setErrorType(const Error::ErrorType_t type) {
        this->_type = type;
    }

    Error createError(const Error::ErrorType_t type) {
        pacman::Error err;
        err.setErrorType(type);
        return err;
    }
}
