#include "PacmanEntities.hpp"

namespace pacman {
    AEntity::AEntity(EntityType type, Vector2D position, bool visibility) {
        this->entityType = type;
        this->position = position;
        this->visibility = visibility;
    }

    EntityType AEntity::getEntityType() const {
        return this->entityType;
    }

    void AEntity::setEntityType(EntityType type) {
        this->entityType = type;
    }

    Vector2D AEntity::getPosition() const {
        return this->position;
    }

    void AEntity::setPosition(Vector2D position) {
        this->position = position;
    }

    bool AEntity::getVisibility() const {
        return this->visibility;
    }

    void AEntity::setVisibility(bool visibility) {
        this->visibility = visibility;
    }

    Player::Player()
        : AEntity(PLAYER, Vector2D(12, 10), true)
    {}

    void Player::move(Input direction, Map map) {
        if (map.empty())
            throw quickError(Error::MAP_UNINITIALIZED);
        const int x = this->position.x;
        const int y = this->position.y;
        switch (direction) {
            case UP:
                if (map[y - 1][x] == WALL)
                    return;
                this->position.y--;
            break;
            case DOWN:
                if (map[y + 1][x] == WALL)
                    return;
                this->position.y++;
            break;
            case LEFT:
                if (map[y][x - 1] == WALL)
                    return;
                this->position.x--;
            break;
            case RIGHT:
                if (map[y][x + 1] == WALL)
                    return;
                this->position.x++;
            break;
            default:
                throw quickError(Error::FORBIDDEN_ACTION);
        }
    }
}
