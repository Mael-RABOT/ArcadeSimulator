#ifndef PACMAN_ENTITIES
    #define PACMAN_ENTITIES

    #include <cmath>
    #include "Type.hpp"
    #include "PacmanError.hpp"

namespace pacman {
    #define PLAYER_SPEED 0.25
    #define CHASE_SPEED 0.2
    #define FLEE_SPEED 0.1

    class AEntity : public IEntity {
    public:
        AEntity(EntityType type, Vector2D position, bool visibility);
        ~AEntity() = default;
        EntityType getEntityType() const override;
        void setEntityType(EntityType type) override;
        Vector2D getPosition() const override;
        void setPosition(Vector2D position) override;
        bool getVisibility() const override;
        void setVisibility(bool visibility) override;
    };

    class Player : public AEntity {
    private:
        std::size_t idle = 0;
    public:
        Player();
        ~Player() = default;
        void move(Input direction, Map map);
        void kill();
        void waiting();
    };

    class Enemy : public AEntity {
    private:
        float speed = CHASE_SPEED;
        std::size_t idle = 0;
        EntityType type;
        bool isOut = false;
        Input currentDirection = QUIT;

        Input leaving();
        Input runAway(Player player, Map map);
        Input angryChoice(Player player, Map map);
        Input dummyChoice(Map map);
    public:
        Enemy(Vector2D position, EntityType type);
        ~Enemy() = default;
        Input chooseDirection(Player player, Map map);
        void move(Input direction, Map map);
        void vulnerable(bool set);
        void waiting(std::size_t deltaTime);
        void kill(std::size_t deltaTime);
        EntityType getType();
    };

    class AItem : public AEntity {
    private:
        std::size_t value;
    public:
        AItem(EntityType type, Vector2D position, std::size_t value);
        ~AItem() = default;
        std::size_t getPoints() const;
    };

    class Pacdot : public AItem {
    public:
        Pacdot(Vector2D position);
        ~Pacdot() = default;
    };

    class Pacgum : public AItem {
    public:
        Pacgum(Vector2D position);
        ~Pacgum() = default;
    };

    class Bonus : public AItem {
    public:
        Bonus(Vector2D position, EntityType type);
        ~Bonus() = default;
    };

    class Life : public AEntity {
    public:
        Life(Vector2D position);
        ~Life() = default;
    };

    class Door : public AEntity {
    public:
        Door();
        ~Door() = default;
    };
}

#endif
