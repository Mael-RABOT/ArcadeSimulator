#include "GamePacman.hpp"
#include <iostream>///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GamePacman::GamePacman()
    : player(pacman::Player())
{}

void GamePacman::handleInput(std::size_t deltaTime, Input input) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
    if (this->entities.empty())
        throw pacman::quickError(pacman::Error::ENTITIES_UNINITIALIZED);
    switch (input) {
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            this->player.move(input, this->map);
            std::cout << "Player x=" << this->player.getPosition().x << " y=" << this->player.getPosition().y << std::endl;////////////////////////////
        break;
        case QUIT:
        break;
        case MENU:
        break;
        case ACTION:
        break;
    }
}

void GamePacman::update(std::size_t deltaTime) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
    if (this->entities.empty())
        throw pacman::quickError(pacman::Error::ENTITIES_UNINITIALIZED);
}

std::vector<std::string> GamePacman::getInstruction() {
    std::vector<std::string> list = {std::string("")};
    return list;
}

EntitiesDescription GamePacman::getEntities() {
    if (!this->entitiesDescriptor.empty())
        this->entitiesDescriptor.clear();
    if (!this->entities.empty())
        this->entities.clear();
    this->entities.push_back(std::ref(this->player));
    for (std::vector<std::reference_wrapper<IEntity>>::iterator i = this->entities.begin(); i != this->entities.end(); i++) {
        this->entitiesDescriptor.push_back(std::pair(i->get().getEntityType(), i->get().getPosition()));
    }
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
