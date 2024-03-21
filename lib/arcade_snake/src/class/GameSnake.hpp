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

        void handleInput(std::size_t deltaTime, Input input) override;
        void update(std::size_t deltaTime) override;

        std::vector<std::string> getInstruction() override;
        EntityDescription getEntities() override;

        Map getMap() override;
        std::map<EntityType, std::string> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;
};
