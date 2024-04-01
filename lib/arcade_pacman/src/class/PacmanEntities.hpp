#ifndef PACMAN_ENTITIES
    #define PACMAN_ENTITIES

    #include "Type.hpp"
    #include "PacmanError.hpp"

namespace pacman {
    class AEntity : public IEntity {
    public:
        AEntity(EntityType type, Vector2D position, bool visibility);
        EntityType getEntityType() const override;
        void setEntityType(EntityType type) override;
        Vector2D getPosition() const override;
        void setPosition(Vector2D position) override;
        bool getVisibility() const override;
        void setVisibility(bool visibility) override;
    };

    class Player : public AEntity {
    public:
        Player();
        void move(Input direction, Map map);
        void kill();
    };
}

#endif
