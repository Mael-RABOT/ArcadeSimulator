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

std::vector<std::pair<std::string, Vector2D>> GameSnake::getTexts() {
    return std::vector<std::pair<std::string, Vector2D>>();
}

std::vector<std::reference_wrapper<IEntity>> GameSnake::initEntities(Map &map) {
    return std::vector<std::reference_wrapper<IEntity>>();
}
