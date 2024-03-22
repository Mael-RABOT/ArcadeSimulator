#include "../../../Class/Manager.hpp"

namespace CoreModule {
    KiwiBool Manager::handleEvent(auto elapsed_seconds) {
        for (auto &input : this->displayModule->event()) {
            if (input == Input::QUIT) {
                if (this->displayModule) delete this->displayModule;
                if (this->gameModule) delete this->gameModule;
                return NotKiwi;
            }
            if (input == Input::MENU) {
                this->loadLibraries("./lib/arcade_menu.so", Signature::GAME);
                return Kiwi;
            }
            this->gameModule->handleInput(elapsed_seconds.count(), input);
        }
        return Kiwi;
    }

    void Manager::handleEntities() {
        if (!this->gameModule) {
            std::cerr << "Error: game module not loaded" << std::endl;
            return;
        }
        if (!this->displayModule) {
            std::cerr << "Error: display module not loaded" << std::endl;
            return;
        }
        auto entities = this->gameModule->getEntities();
        this->displayModule->updateEntity(entities);
    }

    void Manager::defaultLoad() {
        this->gameModule = nullptr;
        this->displayModule = nullptr;

        this->loadLibraries(initialGraphicalLib, Signature::GRAPHICAL);
        this->loadLibraries("./lib/arcade_menu.so", Signature::GAME);
        mainLoop();
    }

    void Manager::mainLoop() {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto last_update_time = start_time;

        try {
            while (this->isRunning) {
                    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::high_resolution_clock::now() - start_time);
                    auto current_time = std::chrono::high_resolution_clock::now();
                    auto elapsed_time = current_time - start_time;
                    auto time_since_last_update = current_time - last_update_time;

                    if (!this->gameModule || !this->displayModule) {
                        throw CoreError("Missing library in main loop");
                    }

                    if (!this->handleEvent(elapsed_seconds)) return;
                    if (time_since_last_update.count() >= 1.0 / 60.0) {
                        this->displayModule->clear();
                        this->gameModule->update(elapsed_time.count());
                        last_update_time = current_time;
                        this->handleInstruction();
                        this->handleEntities();
                        this->displayModule->display();
                    }
            }
        } catch (ArcadeException const &error) {
            std::cerr << "Error on Library" << std::endl;
            this->defaultLoad();
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
        if (lib.empty()) return;
        this->loadLibraries(lib, static_cast<Signature>(signature));
    }

    void Manager::handleInstruction() {
        if (!this->gameModule) return;
        for (auto &instruction : this->gameModule->getInstruction()) {
            if (instruction.find("displayText") != std::string::npos) {
                this->handleText(instruction);
            }
            if (instruction.find("loadLibrary") != std::string::npos) {
                std::cout << "-----\nLOAD instruction: " << instruction << std::endl;
                this->handleLibrary(instruction);
            }
        }
    }
}
