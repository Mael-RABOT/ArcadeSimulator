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
        : AEntity(PLAYER, Vector2D(10, 12), true)
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
        this->entityType = PLAYER_MOVE;
    }

    void Player::kill() {
        this->entityType = PLAYER_DYING;
    }

    void Player::waiting() {
        if (this->entityType == PLAYER_MOVE) {
            this->idle++;
            if (this->idle >= 60) {
                this->entityType = PLAYER;
                this->idle = 0;
            }
        } else {
            return;
        }
    }

    Enemy::Enemy(Vector2D position, std::size_t type)
        : AEntity((EntityType)(ENEMY1 + type), position, true), type(type)
    {}

    void Enemy::move(Map map) {
    }

    void Enemy::kill() {
        this->entityType = ENEMY5;
    }

    void Enemy::waiting() {
        if (this->entityType == ENEMY5) {
            this->idle++;
            if (this->idle >= 60) {
                this->entityType = (EntityType)(ENEMY1 + this->type);
                this->idle = 0;
            }
        } else {
            return;
        }
    }

    AItem::AItem(EntityType type, Vector2D position, std::size_t value)
        : AEntity(type, position, true), value(value)
    {}

    std::size_t AItem::getPoints() const {
        return this->value;
    }

    Pacdot::Pacdot(Vector2D position)
        : AItem(ITEM1, position, 10)
    {}

    Pacgum::Pacgum(Vector2D position)
        : AItem(ITEM2, position, 10)
    {}

    Bonus::Bonus(Vector2D position, std::size_t rarity)
        : AItem((EntityType)(ITEM3 + rarity), position, 100 * (rarity + 1))
    {}
}
