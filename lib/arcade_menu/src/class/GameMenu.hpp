#pragma once

#include <dlfcn.h>
#include <dirent.h>

#include "IGameModule.hpp"

class GameMenu : public IGameModule {
    private:
        std::vector<std::string> gamesList;
        std::vector<std::string> graphicalList;
        std::vector<std::string>::iterator gameSelector;
        std::vector<std::string>::iterator graphicalSelector;
        std::vector<std::string> instruction;

    public:
        GameMenu();
        ~GameMenu();

        std::size_t getScore() override;
        GameState getState() override;
        std::size_t getLive() override;

        void handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) override;
        void update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) override;

        std::vector<std::string> getInstruction() override;

        std::vector<std::reference_wrapper<IEntity>> initEntities(Map &map) override;
        std::map<EntityType, std::string> getSpriteDict() override;

        Signature getLibSignature(std::string const &path);
        void initLibSelectors();

        void formatLoadInstruction();
        void formatTextInstruction();
};
