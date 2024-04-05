#include "GameMenu.hpp"

GameMenu::GameMenu() { this->loader(); }

void GameMenu::loader() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./lib")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string filename = ent->d_name;
            if (filename.substr(filename.find_last_of(".") + 1) == "so") {
                std::string path = "./lib/" + filename;
                Signature signature = getLibSignature(path);
                if (signature == GAME) {
                    gamesList.push_back(path);
                } else if (signature == GRAPHICAL) {
                    graphicalList.push_back(path);
                }
            }
        }
        closedir (dir);
    }
    gameIndex = 0;
    graphicalIndex = 0;
    this->formatTextInstruction();
    this->isNameSelector = true;
    this->index = 0;
    this->username = "USERNAME";
}

GameMenu::~GameMenu() {}

void GameMenu::handleInput(std::size_t deltaTime, Input input) {
    if (isNameSelector) {
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
                isNameSelector = false;
            default:
                break;
        }
    } else {
        switch (input) {
            case Input::UP:
                if (gameIndex == 0)
                    gameIndex = gamesList.size() - 1;
                else
                    gameIndex--;
                break;
            case Input::DOWN:
                if (gameIndex == gamesList.size() - 1)
                    gameIndex = 0;
                else
                    gameIndex++;
                break;
            case Input::LEFT:
                if (graphicalIndex == 0)
                    graphicalIndex = graphicalList.size() - 1;
                else
                    graphicalIndex--;
                break;
            case Input::RIGHT:
                if (graphicalIndex == graphicalList.size() - 1)
                    graphicalIndex = 0;
                else
                    graphicalIndex++;
                break;
            case Input::ACTION:
                formatTextInstruction();
                formatLoadInstruction();
                formatUsernameInstruction();
            default:
                break;
        }
    }
}

void GameMenu::update(std::size_t deltaTime) {}

std::vector<std::string> GameMenu::getInstruction() {
    this->formatTextInstruction();
    this->formatUsernameInstruction();
    return std::move(this->instruction);
}

EntitiesDescription GameMenu::getEntities() {
    EntitiesDescription entities;
    return entities;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameMenu::getSpriteDict() {
    return std::map<EntityType, std::pair<std::string, std::size_t>>();
}

std::map <StaticScreen, std::string> GameMenu::getStaticScreen() {
    return std::map<StaticScreen, std::string>();
}

Signature GameMenu::getLibSignature(const std::string &path) {
    void *lib = dlopen(path.c_str(), RTLD_LAZY);
    if (lib == nullptr) return static_cast<Signature>(-1);
    Signature (*getSignature)() = (Signature (*)())dlsym(lib, "getSignature");
    if (getSignature == nullptr) return static_cast<Signature>(-1);
    Signature signature = getSignature();
    dlclose(lib);
    return signature;
}

void GameMenu::formatLoadInstruction() {
    std::string game = "loadLibrary " + gamesList[gameIndex] + " " + std::to_string(Signature::GAME);
    std::string graphical = "loadLibrary " + graphicalList[graphicalIndex] + " " + std::to_string(Signature::GRAPHICAL);
    instruction.push_back(game);
    instruction.push_back(graphical);
}

void GameMenu::formatTextInstruction() {
    int rdi = 2;
    for (std::size_t i = 0; i < username.size(); i++) {
        std::string truthValue = (i == index) && isNameSelector? "true" : "false";
        instruction.push_back("displayText " + std::string(1, username[i]) + " " + std::to_string((i * 2) + 1) + " " + std::to_string(0) + " " + truthValue);
    }

    instruction.push_back("displayText Game 0 " + std::to_string(rdi++) + " false");
    for (auto &game : gamesList) {
        instruction.push_back("displayText " + game + " 0 " + std::to_string(rdi++) + (game == gamesList[gameIndex] && !isNameSelector ? " true" : " false"));
    }
    rdi++;
    instruction.push_back("displayText Graphical 0 " + std::to_string(rdi++) + " false");
    for (auto &graphical : graphicalList) {
        instruction.push_back("displayText " + graphical + " 0 " + std::to_string(rdi++) + (graphical == graphicalList[graphicalIndex] && !isNameSelector ? " true" : " false"));
    }
}

void GameMenu::formatUsernameInstruction() {
    instruction.push_back("username " + username);
}

Map& GameMenu::getMap() {
    return this->map;
}
