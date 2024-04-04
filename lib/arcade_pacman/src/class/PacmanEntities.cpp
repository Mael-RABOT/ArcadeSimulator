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
        int x = std::round(this->position.x);
        int y = std::round(this->position.y);
        switch (direction) {
            case UP:
                if (map[y - 1][x] == WALL && this->position.y < ((float)y + PLAYER_SPEED))
                    this->position.y = std::round(this->position.y);
                else
                    this->position.y = this->position.y - PLAYER_SPEED;
            break;
            case DOWN:
                y = this->position.y;
                if (map[y + 1][x] == WALL)
                    this->position.y = (int)this->position.y;
                else
                    this->position.y = this->position.y + PLAYER_SPEED;
            break;
            case LEFT:
                if (map[y][x - 1] == WALL && this->position.x < ((float)x + PLAYER_SPEED))
                    this->position.x = std::round(this->position.x);
                else if (x - 1 < 0)
                    this->position.x = map[y].size() - 1;
                else
                    this->position.x = this->position.x - PLAYER_SPEED;
            break;
            case RIGHT:
                x = this->position.x;
                if (map[y][x + 1] == WALL)
                    this->position.x = (int)this->position.x;
                else if (x + 1 == (int)(map[y].size()))
                    this->position.x = 0;
                else
                    this->position.x = this->position.x + PLAYER_SPEED;
            break;
            default:
                throw quickError(Error::FORBIDDEN_ACTION);
        }
        this->position.rotation = direction;
        this->entityType = PLAYER_MOVE;
    }

    void Player::kill() {
        this->position.rotation = RIGHT;
        this->entityType = PLAYER_DYING;
    }

    void Player::waiting() {
        if (this->entityType == PLAYER_MOVE) {
            this->idle++;
            if (this->idle >= 60) {
                this->entityType = PLAYER;
                this->position.rotation = RIGHT;
                this->idle = 0;
            }
        } else {
            return;
        }
    }

    Enemy::Enemy(Vector2D position, EntityType type)
        : AEntity(type, position, true), type(type)
    {}

    void Enemy::move(Input direction, Map map) {
        if (map.empty())
            throw quickError(Error::MAP_UNINITIALIZED);
        int x = std::round(this->position.x);
        int y = std::round(this->position.y);
        switch (direction) {
            case UP:
                if (map[y - 1][x] == WALL && this->position.y < ((float)y + this->speed))
                    this->position.y = std::round(this->position.y);
                else
                    this->position.y = this->position.y - this->speed;
            break;
            case DOWN:
                y = this->position.y;
                if (map[y + 1][x] == WALL)
                    this->position.y = (int)this->position.y;
                else
                    this->position.y = this->position.y + this->speed;
            break;
            case LEFT:
                if (map[y][x - 1] == WALL && this->position.x < ((float)x + this->speed))
                    this->position.x = std::round(this->position.x);
                else if (x - 1 < 0)
                    this->position.x = map[y].size() - 1;
                else
                    this->position.x = this->position.x - this->speed;
            break;
            case RIGHT:
                x = this->position.x;
                if (map[y][x + 1] == WALL)
                    this->position.x = (int)this->position.x;
                else if (x + 1 == (int)(map[y].size()))
                    this->position.x = 0;
                else
                    this->position.x = this->position.x + this->speed;
            break;
            default:
                throw quickError(Error::FORBIDDEN_ACTION);
        }
        this->position.rotation = this->inputConversion(direction);
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

    Input Enemy::inputConversion(Input direction) const {
        switch (direction) {
            case UP: return RIGHT;
            case DOWN: return LEFT;
            case RIGHT: return UP;
            case LEFT: return DOWN;
            default: return direction;
        }
    }

    RedGhost::RedGhost()
        : Enemy(Vector2D(9, 9, DOWN), ENEMY1)
    {}

    Input RedGhost::chooseDirection(Player player, Map map) {
        return RIGHT;
    }

    OrangeGhost::OrangeGhost()
        : Enemy(Vector2D(9, 10, DOWN), ENEMY2)
    {}

    Input OrangeGhost::chooseDirection(Player player, Map map) {
        return RIGHT;
    }

    BlueGhost::BlueGhost()
        : Enemy(Vector2D(11, 9, UP), ENEMY3)
    {}

    Input BlueGhost::chooseDirection(Player player, Map map) {
        return RIGHT;
    }

    PinkGhost::PinkGhost()
        : Enemy(Vector2D(11, 10, UP), ENEMY4)
    {}

    Input PinkGhost::chooseDirection(Player player, Map map) {
        return RIGHT;
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

    Life::Life(Vector2D position)
        : AItem(PLAYER, position, 10)
    {}
}
