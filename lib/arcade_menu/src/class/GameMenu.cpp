#include "GameMenu.hpp"

GameMenu::GameMenu() {}

GameMenu::~GameMenu() {}

std::size_t GameMenu::getScore() { return 0; }

GameState GameMenu::getState() { return GameState::RUNNING; }

std::size_t GameMenu::getLive() { return 0; }

void GameMenu::handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) {
    switch (input) {
        case Input::UP:
            if (gameSelector != gamesList.begin()) gameSelector--;
            break;
        case Input::DOWN:
            if (gameSelector != gamesList.end() - 1) gameSelector++;
            break;
        case Input::LEFT:
            if (graphicalSelector != graphicalList.begin()) graphicalSelector--;
            break;
        case Input::RIGHT:
            if (graphicalSelector != graphicalList.end() - 1) graphicalSelector++;
            break;
        case Input::ACTION:
            formatTextInstruction();
            formatLoadInstruction();
        case Input::MENU:
            break;
        case Input::QUIT:
            break;
        default:
            break;
    }
}

void GameMenu::update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) {
    initLibSelectors();
}

std::vector<std::string> GameMenu::getInstruction() { return std::move(instruction); }

std::vector<std::reference_wrapper<IEntity>> GameMenu::initEntities(Map &map) {
    return std::vector<std::reference_wrapper<IEntity>>();
}

std::map <EntityType, std::string> GameMenu::getSpriteDict() {
    return std::map<EntityType, std::string>();
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

void GameMenu::initLibSelectors() {
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
}

void GameMenu::formatLoadInstruction() {
    std::string game = "loadLibrary" + *gameSelector + std::to_string(Signature::GAME);
    std::string graphical = "loadLibrary" + *graphicalSelector + std::to_string(Signature::GRAPHICAL);
    instruction.push_back(game);
    instruction.push_back(graphical);
}

void GameMenu::formatTextInstruction() {
    int rdi = 0;
    instruction.push_back("displayText Graphicals 0 0 false");
    for (auto &graphical : graphicalList) {
        std::string graphicalStr = "displayText" + graphical + std::to_string(rdi) + "0" + (graphical == *graphicalSelector ? "true" : "false");
        instruction.push_back(graphicalStr);
        rdi++;
    }
    instruction.push_back("displayText Games " + std::to_string(rdi) + " 0 false");
    for (auto &game : gamesList) {
        std::string gameStr = "displayText" + game + std::to_string(rdi) + "0" + (game == *gameSelector ? "true" : "false");
        instruction.push_back(gameStr);
        rdi++;
    }

}
