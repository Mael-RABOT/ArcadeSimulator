#include "../../../Class/Manager.hpp"

namespace CoreModule {
    void Manager::MainLoop() {

        if (!this->loader->checkStatus()) { throw ("Error: invalid library status"); }

        auto start = std::chrono::steady_clock::now();
        auto startLoop = std::chrono::steady_clock::now();
        while (1) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            auto elapsedLoop = std::chrono::duration_cast<std::chrono::milliseconds>(now - startLoop).count();
            std::chrono::seconds elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start);

            if (elapsedLoop >= 50) {
                if (!this->HandleEvent(elapsed_seconds)) { return; }
                this->loader->displayModule->clear();
                this->loader->gameModule->update(elapsed);

                this->HandleInstruction();
                this->HandleEntities();

                this->loader->displayModule->display();

                startLoop = now;
            }
        }
    }
}
