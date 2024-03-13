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

        std::size_t getScore() override;
        GameState getState() override;
        std::size_t getLive() override;

        void handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) override;
        void update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) override;

        std::vector<std::pair<std::string, Vector2D>> getTexts() override;
        std::vector<std::reference_wrapper<IEntity>> initEntities(Map &map) override;
};
