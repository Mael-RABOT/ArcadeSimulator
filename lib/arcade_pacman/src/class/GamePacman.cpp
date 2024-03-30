#include "GamePacman.hpp"

void GamePacman::handleInput(std::size_t deltaTime, Input input) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
}

void GamePacman::update(std::size_t deltaTime) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
}

std::vector<std::string> GamePacman::getInstruction() {
    std::vector<std::string> list = {std::string("")};
    return list;
}

EntitiesDescription GamePacman::getEntities() {
    return this->entitiesDescriptor;
}

Map& GamePacman::getMap() {
    if (!this->map.empty())
        return this->map;
    std::ifstream mapFile;
    mapFile.open ("lib/assets/pacman_map.txt");
    if (!mapFile.is_open()) {
        throw pacman::quickError(pacman::Error::MAP_NOT_FOUND);
    }
    std::string line;
    int i = 0;
    while(std::getline(mapFile, line)) {
        if (!this->map.empty() && this->map[i - 1].size() != line.length()) {
            throw pacman::quickError(pacman::Error::MAP_CORRUPTED);
        }
        std::vector<EntityType> mapLine;
        for (std::string::iterator c = line.begin(); c != line.end(); c++) {
            if (*c == '#') {
                mapLine.push_back(WALL);
            } else if (*c == ' ') {
                mapLine.push_back(UNDEFINED);
            } else if (*c != '\n') {
                throw pacman::quickError(pacman::Error::MAP_CORRUPTED);
            }
        }
        this->map.push_back(mapLine);
        i++;
    }
    mapFile.close();
    return this->map;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GamePacman::getSpriteDict() {
    std::map<EntityType, std::pair<std::string, std::size_t>> dict = {
        {EntityType::WALL, {std::string("lib/assets/pacman_wall.png"), 0}},
        {EntityType::PLAYER, {std::string("lib/assets/pacman_player.png"), 0}}
    };
    return dict;
}

std::map<StaticScreen, std::string> GamePacman::getStaticScreen() {
    std::map<StaticScreen, std::string> dict = {
    };
    return dict;
}

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
            message = std::string("PACMAN : ERROR : the map has not been initialized.");
        break;
        default:
            message = std::string("PACMAN : ERROR : Undifined error");
    }
    pacman::Error err(message);
    return err;
}
