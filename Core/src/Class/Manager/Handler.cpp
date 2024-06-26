#include "../../../Class/Manager.hpp"

namespace CoreModule {
    KiwiBool Manager::HandleEvent(std::size_t elapsed) {
        std::vector<Input> events = this->loader->displayModule->event();
        for (auto &event : events) {
            switch (event) {
                case Input::QUIT:
                    return NotKiwi;
                case Input::MENU:
                    this->loader->close(Signature::GAME);
                    this->loader->open("./lib/arcade_menu.so", Signature::GAME);
                    break;
                case Input::RESET:
                    this->loader->close(Signature::GAME);
                    this->loader->open(this->current_game, Signature::GAME);
                    static_cast<void>(this->loader->gameModule->getMap());
                    static_cast<void>(this->loader->gameModule->getEntities());
                    break;
                case Input::NEXT_DI:
                    this->loader->nextDisplay();
                    break;
                case Input::NEXT_GA:
                    this->loader->nextGame();
                    break;
                default:
                    this->loader->gameModule->handleInput(elapsed, event);
            }
        }
        return Kiwi;
    }

    void Manager::HandleTextInstruction(std::string instruction) {
        std::istringstream iss(instruction);
        std::string command, text;
        int x, y;
        bool highlight;

        iss >> command
            >> text
            >> x
            >> y
            >> std::boolalpha >> highlight;
        this->loader->displayModule->updateText(text, {static_cast<float>(x), static_cast<float>(y)}, highlight);
    }

    void Manager::HandleLoadInstruction(std::string instruction) {
        std::istringstream iss(instruction);
        std::string command, lib;
        int signature;
        iss >> command
            >> lib
            >> signature;
        if (lib.empty()) return;
        this->loader->close(static_cast<Signature>(signature));
        this->loader->open(lib, static_cast<Signature>(signature));
        this->loader->displayModule->loadDicts(this->loader->gameModule->getSpriteDict(), this->loader->gameModule->getStaticScreen());
        if (static_cast<Signature>(signature) == Signature::GAME) {
            this->current_game = lib;
        }
    }

    void Manager::HandleInstruction() {
        std::vector<std::string> instructions = this->loader->gameModule->getInstruction();
        if (instructions.empty()) return;
        for (std::string &instruction : instructions) {
            if (instruction.find("displayText") != std::string::npos) {
                this->HandleTextInstruction(instruction);
                continue;
            }
            if (instruction.find("loadLibrary") != std::string::npos) {
                this->HandleLoadInstruction(instruction);
                continue;
            }
            if (instruction.find("username") != std::string::npos) {
                std::istringstream iss(instruction);
                std::string command, username;
                iss >> command
                    >> username;
                this->username = username;
                continue;
            }
        }
    }

    void Manager::HandleEntities() {
        auto map = this->loader->gameModule->getMap();
        this->loader->displayModule->updateMap(map);

        auto entities = this->loader->gameModule->getEntities();
        this->loader->displayModule->updateEntities(entities);
    }
}
