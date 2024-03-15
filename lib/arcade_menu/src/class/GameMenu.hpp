#pragma once

#include <dlfcn.h>
#include <dirent.h>
#include <cstdlib>

#include "IGameModule.hpp"

class GameMenu : public IGameModule {
    private:
        std::vector<std::string> gamesList;
        std::vector<std::string> graphicalList;
        std::vector<std::string>::iterator gameIterator;
        std::vector<std::string>::iterator graphicalIterator;
        std::vector<std::string> instruction;

    public:
        GameMenu();
        ~GameMenu();

        void handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) override;
        void update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) override;

        std::vector<std::string> getInstruction() override;

        Map getMap() override;
        std::vector<std::reference_wrapper<IEntity>> initEntities() override;
        std::map<EntityType, std::string> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;

        Signature getLibSignature(std::string const &path);

        void formatLoadInstruction();
        void formatTextInstruction();

        void loader();
};
