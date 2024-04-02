#ifndef PACMAN_ENTITIES
    #define PACMAN_ENTITIES

    #include "Type.hpp"
    #include "PacmanError.hpp"

namespace pacman {
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
        std::size_t idle = 0;
        Input currentDirection = QUIT;
    public:
        Enemy(Vector2D position, std::size_t type);
        ~Enemy() = default;
        /*void start();
        void move(Map map);
        void kill();
        void waiting();*/
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
        Bonus(Vector2D position, std::size_t rarity);
        ~Bonus() = default;
    };
}

#endif
