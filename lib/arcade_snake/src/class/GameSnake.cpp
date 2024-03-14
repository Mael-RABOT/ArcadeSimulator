#include "GameSnake.hpp"

GameSnake::GameSnake() {
    _state = GameState::RUNNING;
    _score = 0;
    _live = 3;
}

GameSnake::~GameSnake() {}

std::size_t GameSnake::getScore() {
    return _score;
}

GameState GameSnake::getState() {
    return _state;
}

std::size_t GameSnake::getLive() {
    return _live;
}

void GameSnake::handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) {}

void GameSnake::update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) {}

std::vector <std::string> GameSnake::getInstruction() {
    return std::vector<std::string>();
}

std::vector<std::reference_wrapper<IEntity>> GameSnake::initEntities(Map &map) {
    return std::vector<std::reference_wrapper<IEntity>>();
}

std::map <EntityType, std::string> GameSnake::getSpriteDict() {
    return std::map<EntityType, std::string>();
}
