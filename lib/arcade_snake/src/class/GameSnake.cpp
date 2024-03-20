#include "GameSnake.hpp"

GameSnake::GameSnake() {
    _state = GameState::RUNNING;
    _score = 0;
    _live = 3;
    direction.x = 1;
    direction.y = 0;
}

GameSnake::~GameSnake() {}

void GameSnake::handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) {}

void GameSnake::update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) {}

std::vector <std::string> GameSnake::getInstruction() {
    return std::vector<std::string>();
}

EntitiesDescription GameSnake::getEntities() {
    EntitiesDescription entities;
    return entities;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameSnake::getSpriteDict() {
    return std::map<EntityType, std::pair<std::string, std::size_t>>();
}

std::map <StaticScreen, std::string> GameSnake::getStaticScreen() {
    return std::map<StaticScreen, std::string>();
}

Map& GameSnake::getMap() {
    return this->map;
}
