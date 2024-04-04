#include "../../../Class/Manager.hpp"

namespace CoreModule {
    void Manager::MainLoop() {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto last_update_time = start_time;

        if (!this->loader->checkStatus()) { throw ("Error: invalid library status"); }

        int rdi = 0;

        while (1) {
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time);
            auto current_time = std::chrono::high_resolution_clock::now();
            auto elapsed_time = current_time - start_time;
            auto time_since_last_update = current_time - last_update_time;

            if (!this->HandleEvent(elapsed_seconds)) { return; }
            if (time_since_last_update.count() >= 1.0 / (60.0 * 4)) {
                printf("update %d\n", rdi++);
                this->loader->displayModule->clear();

                this->loader->gameModule->update(elapsed_seconds.count());
                last_update_time = current_time;

                this->HandleInstruction();
                this->HandleEntities();

                this->loader->displayModule->display();
            }
        }
    }
}
