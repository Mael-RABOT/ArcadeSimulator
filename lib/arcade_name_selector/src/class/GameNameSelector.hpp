#pragma once

#include <dlfcn.h>
#include <dirent.h>
#include <cstdlib>
#include <iostream>

#include "IGameModule.hpp"

#define MAX_LENGTH 8

class GameNameSelector : public IGameModule {
    private:
        std::string username;
        std::size_t index;
        std::vector<std::string> instruction;

    public:
        GameNameSelector();
        ~GameNameSelector();

        void handleInput(std::size_t deltaTime, Input input) override;
        void update(std::size_t deltaTime) override;

        std::vector<std::string> getInstruction() override;
        EntitiesDescription getEntities() override;

        Map& getMap() override;
        std::map<EntityType, std::pair<std::string, std::size_t>> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;

        void formatTextInstruction();
        void formatUsernameInstruction();
};
