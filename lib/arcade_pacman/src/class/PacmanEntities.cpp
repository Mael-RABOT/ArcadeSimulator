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

    Input Enemy::leaving() {
        if (9.8 < this->position.x && this->position.x < 10.2)
            this->position.x = std::round(this->position.x);
        if (this->position.x < 10)
            return RIGHT;
        if (this->position.x > 10)
            return LEFT;
        return UP;
    }

    Input Enemy::chooseDirection(Player player, Map map) {
        return this->leaving();
    }

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
            case QUIT:
            break;
            default:
                throw quickError(Error::FORBIDDEN_ACTION);
        }
        this->position.rotation = direction;
    }

    void Enemy::vulnerable(bool set) {
        this->entityType = (set) ? ENEMY5 : this->type;
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

    Life::Life(Vector2D position)
        : AEntity(PLAYER, position, true)
    {}

    Door::Door()
        : AEntity(WALL, Vector2D(10,8), true)
    {}
}
