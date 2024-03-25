#pragma once

#include <dlfcn.h>
#include <dirent.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "IGameModule.hpp"

class GamePacman : public IGameModule {
    private:
        std::vector<std::string> gamesList;
        std::vector<std::string> graphicalList;
        std::vector<std::string>::iterator gameIterator;
        std::vector<std::string>::iterator graphicalIterator;
        std::vector<std::string> instruction;
        std::vector<std::reference_wrapper<IEntity>> entities;

    public:
        GamePacman();
        ~GamePacman();

        void handleInput(std::size_t deltaTime, Input input) override;
        void update(std::size_t deltaTime) override;

        std::vector<std::string> getInstruction() override;
        EntitiesDescription getEntities() override;

        Map getMap() override;
        std::map<EntityType, std::string> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;

        void formatTextInstruction();
};
