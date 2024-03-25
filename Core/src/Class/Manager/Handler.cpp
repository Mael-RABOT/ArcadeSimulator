#include "../../../Class/Manager.hpp"

namespace CoreModule {
    KiwiBool Manager::HandleEvent(std::chrono::seconds elapsed_seconds __attribute_maybe_unused__) {
        std::vector<Input> events = this->loader->displayModule->event();
        for (auto &event : events) {
            switch (event) {
                case Input::QUIT:
                    return NotKiwi;
                case Input::MENU:
                    this->loader->close(Signature::GAME);
                    this->loader->open("./lib/arcade_menu.so", Signature::GAME);
                    break;
                default:
                    this->loader->gameModule->handleInput(elapsed_seconds.count(), event);
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
        this->loader->displayModule->updateText(text, {x, y}, highlight);
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
        if (lib.find("arcade_menu") != std::string::npos) {
            this->isMenu = Kiwi;
        } else {
            this->isMenu = NotKiwi;
        }
    }

    void Manager::HandleInstruction() {
        std::vector<std::string> instructions = this->loader->gameModule->getInstruction();
        if (isMenu) {
            instructions.push_back("displayText " + this->username + " 0 0 true");
        }
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
                this->loader->close(Signature::GAME);
                this->loader->open("./lib/arcade_menu.so", Signature::GAME);
                this->isMenu = Kiwi;
                continue;
            }
        }
    }

    void Manager::HandleEntities() {
        auto entities = this->loader->gameModule->getEntities();
        this->loader->displayModule->updateEntities(entities);

        auto map = this->loader->gameModule->getMap();
        this->loader->displayModule->updateMap(map);
    }
}
