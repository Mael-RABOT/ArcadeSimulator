#pragma once

#include "IGameModule.hpp"

class GameSnake : public IGameModule {
    private:
        GameState _state;
        std::size_t _score;
        std::size_t _live;
        Vector2D direction;
        std::vector<std::reference_wrapper<IEntity>> player;
        void initMap();
        void initPlayer();
        void movePlayer();
        bool collide();
        void turnLeft();
        void turnRight();
    protected:
        Map map;
        std::vector<std::reference_wrapper<IEntity>> entities;
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
