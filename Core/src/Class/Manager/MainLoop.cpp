#include "../../../Class/Manager.hpp"

namespace CoreModule {
    KiwiBool Manager::handleEvent() {
        for (auto &input : this->displayModule->event()) {
            if (input == Input::QUIT) {
                delete this->displayModule;
                return NotKiwi;
            }
        }
        return Kiwi;
    }

    void Manager::mainLoop() {
        while (this->isRunning) {
            this->displayModule->clear();
            if (!this->handleEvent()) return;
            this->displayModule->display();
        }
    }
}
