#pragma once

#include <random>

#include "IGameModule.hpp"

class AEntity : public IEntity {
    protected:
        EntityType entityType;
        Vector2D position;
        bool visibility;

    public:
        AEntity();
        ~AEntity();
        EntityType getEntityType() const override;
        void setEntityType(EntityType) override;
        Vector2D getPosition() const override;
        void setPosition(Vector2D position) override;
        bool getVisibility() const override;
        void setVisibility(bool visibility) override;
};

class PlayerElement : public AEntity {
};

class Food : public AEntity {
};

class GameSnake : public IGameModule {
    private:
        GameState _state;
        std::size_t _score;
        std::size_t _live;
        Vector2D direction;
        std::vector<PlayerElement> player;
        void initPlayer();
        void movePlayer();
        bool collide();
        void turn(bool trigonometric);
        Vector2D applePos;
        void spawnApple();

    protected:
        Map map;
        std::vector<IEntity> entities;
        EntitiesDescription entityDescriptor;

    public:
        GameSnake();
        ~GameSnake();

        void handleInput(std::size_t deltaTime, Input input) override;
        void update(std::size_t deltaTime) override;

        std::vector<std::string> getInstruction() override;

        EntitiesDescription getEntities() override;

        Map& getMap() override;
        std::map<EntityType, std::pair<std::string, std::size_t>> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;
};
