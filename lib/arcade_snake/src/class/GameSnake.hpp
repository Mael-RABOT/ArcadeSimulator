#pragma once

#include "IGameModule.hpp"

class GameSnake : public IGameModule {
    private:
        GameState _state;
        std::size_t _score;
        std::size_t _live;

    public:
        GameSnake();
        ~GameSnake();

        void handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) override;
        void update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) override;

        std::vector<std::string> getInstruction() override;

        Map getMap() override;
        std::vector<std::reference_wrapper<IEntity>> initEntities() override;
        std::map<EntityType, std::string> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;
};
