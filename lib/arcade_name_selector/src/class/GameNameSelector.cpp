#include "GameNameSelector.hpp"

GameNameSelector:: GameNameSelector() {
    username = "USERNAME";
    index = 0;
    this->formatTextInstruction();
}

GameNameSelector::~ GameNameSelector() {}

void GameNameSelector::handleInput(std::size_t deltaTime, Input input) {
    switch (input) {
        case Input::UP:
            username[index] = (username[index] == 'Z') ? 'A' : username[index] + 1;
            break;
        case Input::DOWN:
            username[index] = (username[index] == 'A') ? 'Z' : username[index] - 1;
            break;
        case Input::LEFT:
            index = (index == 0) ? username.size() - 1 : index - 1;
            break;
        case Input::RIGHT:
            index = (index == username.size() - 1) ? 0 : index + 1;
            break;
        case Input::ACTION:
            formatTextInstruction();
            formatUsernameInstruction();
        default:
            break;
    }
}

void GameNameSelector::update(std::size_t deltaTime) {}

std::vector<std::string> GameNameSelector::getInstruction() {
    auto instructions = instruction;
    this->formatTextInstruction();

    for (auto &i : instruction) {
        if (i.find("username") != std::string::npos) {
            instructions.erase(instructions.begin());
        }
    }

    return instructions;
}

EntitiesDescription GameNameSelector::getEntities() {
    EntitiesDescription entities;
    return entities;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameNameSelector::getSpriteDict() {
    return std::map<EntityType, std::pair<std::string, std::size_t>>();
}

std::map <StaticScreen, std::string> GameNameSelector::getStaticScreen() {
    return std::map<StaticScreen, std::string>();
}

void GameNameSelector::formatTextInstruction() {
    for (std::size_t i = 0; i < username.size(); i++) {
        std::string truthValue = (i == index) ? "true" : "false";
        instruction.push_back("displayText " + std::string(1, username[i]) + " " + std::to_string((i * 2) + 1) + " " + std::to_string(0) + " " + truthValue);
    }
}

void GameNameSelector::formatUsernameInstruction() {
    instruction.push_back("username " + username);
}

Map& GameNameSelector::getMap() {
    return this->map;
}
