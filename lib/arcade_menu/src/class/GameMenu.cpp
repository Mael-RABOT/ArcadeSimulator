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
    gameIterator = gamesList.begin();
    graphicalIterator = graphicalList.begin();
    this->formatTextInstruction();
}

GameMenu::~GameMenu() {}

void GameMenu::handleInput(std::size_t deltaTime, Input input) {
    switch (input) {
        case Input::UP:
            if (gameIterator != gamesList.begin())
                gameIterator--;
            else
                gameIterator = gamesList.end();
            break;
        case Input::DOWN:
            if (gameIterator != gamesList.end())
                gameIterator++;
            else
                gameIterator = gamesList.begin();
            break;
        case Input::LEFT:
            if (graphicalIterator != graphicalList.begin())
                graphicalIterator--;
            else
                graphicalIterator = graphicalList.end();
            break;
        case Input::RIGHT:
            if (graphicalIterator != graphicalList.end())
                graphicalIterator++;
            else
                graphicalIterator = graphicalList.begin();
            break;
        case Input::ACTION:
            formatTextInstruction();
            formatLoadInstruction();
        default:
            break;
    }
}

void GameMenu::update(std::size_t deltaTime) {}

std::vector<std::string> GameMenu::getInstruction() {
    auto instructions = instruction;
    this->formatTextInstruction();

    for (auto &i : instruction) {
        if (i.find("loadLibrary") != std::string::npos) {
            instructions.erase(instructions.begin());
        }
    }

    return instructions;
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
    std::string game = "loadLibrary " + *gameIterator + " " + std::to_string(Signature::GAME);
    std::string graphical = "loadLibrary " + *graphicalIterator + " " + std::to_string(Signature::GRAPHICAL);
    instruction.push_back(game);
    instruction.push_back(graphical);
}

void GameMenu::formatTextInstruction() {
    int rdi = 2;
    instruction.push_back("displayText Game 1 0 false");
    for (auto &game : gamesList) {
        instruction.push_back("displayText " + game + " 0 " + std::to_string(rdi++) + (game == *gameIterator ? " true" : " false"));
    }
    instruction.push_back("displayText Graphical 0 " + std::to_string(rdi++) + " false");
    for (auto &graphical : graphicalList) {
        instruction.push_back("displayText " + graphical + " 0 " + std::to_string(rdi++) + (graphical == *graphicalIterator ? " true" : " false"));
    }
}

Map GameMenu::getMap() {
    Map map;
    return map;
}
