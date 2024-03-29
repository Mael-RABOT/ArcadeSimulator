#include "GameSnake.hpp"

GameSnake::GameSnake() {
    _state = GameState::RUNNING;
    _score = 0;
    _live = 3;
}

GameSnake::~GameSnake() {}

void GameSnake::handleInput(std::size_t deltaTime, Input input) {}

void GameSnake::update(std::size_t deltaTime) {}

std::vector <std::string> GameSnake::getInstruction() {
    return std::vector<std::string>();
}

EntityDescription GameSnake::getEntities() {
    EntityDescription entities;
    return entities;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameSnake::getSpriteDict() {
    return std::map<EntityType, std::pair<std::string, std::size_t>>();
}

std::map <StaticScreen, std::string> GameSnake::getStaticScreen() {
    return std::map<StaticScreen, std::string>();
}

Map GameSnake::getMap() {
    Map map;
    return map;
}
