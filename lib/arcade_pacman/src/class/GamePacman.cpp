#include "GamePacman.hpp"

GamePacman::GamePacman() {}

GamePacman::~GamePacman() {}

void GamePacman::handleInput(std::size_t deltaTime, Input input) {
    switch (input) {
        case Input::UP:
            break;
        case Input::DOWN:
            break;
        case Input::LEFT:
            break;
        case Input::RIGHT:
            break;
        case Input::ACTION:
            break;
        default:
            break;
    }
}

void GamePacman::update(std::size_t deltaTime) {}

std::vector<std::string> GamePacman::getInstruction() {
    return this->instruction;
}

EntitiesDescription GamePacman::getEntities() {
    EntitiesDescription entities;
    return entities;
}

std::map <EntityType, std::string> GamePacman::getSpriteDict() {
    return std::map<EntityType, std::string>();
}

std::map <StaticScreen, std::string> GamePacman::getStaticScreen() {
    return std::map<StaticScreen, std::string>();
}

void GamePacman::formatTextInstruction() {
    int rdi = 1;
    instruction.push_back("displayText Game 0 0 false");
    for (auto &game : gamesList) {
        instruction.push_back("displayText " + game + " 0 " + std::to_string(rdi++) + (game == *gameIterator ? " true" : " false"));
    }
    instruction.push_back("displayText Graphical 0 " + std::to_string(rdi++) + " false");
    for (auto &graphical : graphicalList) {
        instruction.push_back("displayText " + graphical + " 0 " + std::to_string(rdi++) + (graphical == *graphicalIterator ? " true" : " false"));
    }
}

Map GamePacman::getMap() {
    Map map;
    return map;
}
