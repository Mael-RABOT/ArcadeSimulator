#include "../../../Class/Manager.hpp"

namespace CoreModule {
    KiwiBool Manager::handleEvent(auto elapsed_seconds) {
        for (auto &input : this->displayModule->event()) {
            if (input == Input::QUIT) {
                delete this->displayModule;
                return NotKiwi;
            }
            this->gameModule->handleInput(elapsed_seconds.count(), input, this->entities);
        }
        return Kiwi;
    }

    void Manager::mainLoop() {
        while (this->isRunning) {
            std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - this->start;
            if (elapsed_seconds.count() > 1.0 / 60.0) {
                this->displayModule->clear();

                if (!this->handleEvent(elapsed_seconds)) return;
                this->gameModule->update(elapsed_seconds.count(), this->entities);

                this->handleInstruction();

                this->displayModule->display();
                this->start = std::chrono::system_clock::now();
            }
        }
    }

    void Manager::handleText(std::string instruction) {
        std::istringstream iss(instruction);
        std::string command, text;
        int x, y;
        bool highlight;

        iss >> command
            >> text
            >> x
            >> y
            >> std::boolalpha >> highlight;
        this->displayModule->updateText(text, {x, y}, highlight);
    }

    void Manager::handleLibrary(std::string instruction) {
        std::istringstream iss(instruction);
        std::string command, lib;
        int signature;
        iss >> command
            >> lib
            >> signature;
        this->loadLibraries(lib, static_cast<Signature>(signature));
    }

    void Manager::handleInstruction() {
        std::map<std::string, std::function<void(std::string)>> instructions = {
                {"displayText", [this](std::string instruction){ this->handleText(instruction); }},
                {"loadLibrary", [this](std::string instruction){ this->handleLibrary(instruction); }},
        };

        if (!this->gameModule) return;
        for (auto &instruction : this->gameModule->getInstruction())
            if (instructions.find(instruction) != instructions.end()) instructions[instruction](instruction);
    }
}
