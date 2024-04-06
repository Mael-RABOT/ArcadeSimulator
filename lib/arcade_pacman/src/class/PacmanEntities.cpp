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
                if (map[y - 1][x] == WALL || std::round(this->position.x) != this->position.x)
                    this->position.y = std::round(this->position.y);
                else
                    this->position.y = this->position.y - PLAYER_SPEED;
            break;
            case DOWN:
                y = this->position.y;
                if (map[y + 1][x] == WALL || std::round(this->position.x) != this->position.x || (x == 10 && y == 7))
                    this->position.y = (int)this->position.y;
                else
                    this->position.y = this->position.y + PLAYER_SPEED;
            break;
            case LEFT:
                if (map[y][x - 1] == WALL || std::round(this->position.y) != this->position.y)
                    this->position.x = std::round(this->position.x);
                else if (x - 1 < 0)
                    this->position.x = map[y].size() - 1;
                else
                    this->position.x = this->position.x - PLAYER_SPEED;
            break;
            case RIGHT:
                x = this->position.x;
                if (map[y][x + 1] == WALL || std::round(this->position.y) != this->position.y)
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

    Input Enemy::runAway(Player player, Map map) {
        int x = std::round(this->position.x);
        int y = std::round(this->position.y);
        if (!(map[y - 1][x] != WALL && player.getPosition().y > y) &&
            !(map[y + 1][x] != WALL && player.getPosition().y < y) &&
            !(map[y][x - 1] != WALL && player.getPosition().x > x) &&
            !(map[y][x + 1] != WALL && player.getPosition().x < x))
            return this->currentDirection;
        while (1) {
            int var = std::rand();
            if (map[y - 1][x] != WALL && var % 2 == 0 && player.getPosition().y > y) {
                this->position.x = std::round(this->position.x);
                return UP;
            } if (map[y + 1][x] != WALL && var % 3 == 0 && player.getPosition().y < y) {
                this->position.x = std::round(this->position.x);
                return DOWN;
            } if (map[y][x - 1] != WALL && var % 5 == 0 && player.getPosition().x > x) {
                this->position.y = std::round(this->position.y);
                return LEFT;
            } if (map[y][x + 1] != WALL && var % 7 == 0 && player.getPosition().x < x) {
                this->position.y = std::round(this->position.y);
                return RIGHT;
            }
        }
    }

    Input Enemy::angryChoice(Player player, Map map) {
        int x = std::round(this->position.x);
        int y = std::round(this->position.y);
        if (!(map[y - 1][x] != WALL && player.getPosition().y < y) &&
            !(map[y + 1][x] != WALL && player.getPosition().y > y) &&
            !(map[y][x - 1] != WALL && player.getPosition().x < x) &&
            !(map[y][x + 1] != WALL && player.getPosition().x > x))
            return this->currentDirection;
        while (1) {
            int var = std::rand();
            if (map[y - 1][x] != WALL && var % 2 == 0 && player.getPosition().y < y) {
                this->position.x = std::round(this->position.x);
                return UP;
            } if (map[y + 1][x] != WALL && var % 3 == 0 && player.getPosition().y > y) {
                this->position.x = std::round(this->position.x);
                return DOWN;
            } if (map[y][x - 1] != WALL && var % 5 == 0 && player.getPosition().x < x) {
                this->position.y = std::round(this->position.y);
                return LEFT;
            } if (map[y][x + 1] != WALL && var % 7 == 0 && player.getPosition().x > x) {
                this->position.y = std::round(this->position.y);
                return RIGHT;
            }
        }
    }

    Input Enemy::dummyChoice(Map map) {
        int x = std::round(this->position.x);
        int y = std::round(this->position.y);
        while (1) {
            int var = std::rand();
            if (map[y - 1][x] != WALL && var % 2 == 0) {
                this->position.x = std::round(this->position.x);
                return UP;
            } if (map[y + 1][x] != WALL && var % 3 == 0) {
                this->position.x = std::round(this->position.x);
                return DOWN;
            } if (map[y][x - 1] != WALL && var % 5 == 0) {
                this->position.y = std::round(this->position.y);
                return LEFT;
            } if (map[y][x + 1] != WALL && var % 7 == 0) {
                this->position.y = std::round(this->position.y);
                return RIGHT;
            }
        }
    }

    Input Enemy::chooseDirection(Player player, Map map) {
        if (std::round(this->position.x) == 10 && this->position.y == 7)
            this->isOut = true;
        if (!this->isOut)
            return this->leaving();
        if (std::round(this->position.x) == this->position.x && std::round(this->position.y) == this->position.y) {
            switch (this->entityType) {
                case ENEMY1:
                case ENEMY3:
                    this->currentDirection = this->dummyChoice(map);
                break;
                case ENEMY2:
                case ENEMY4:
                    this->currentDirection = this->angryChoice(player, map);
                break;
                case ENEMY5:
                    this->currentDirection = this->runAway(player, map);
                break;
                case ENEMY5_DYING:
                    this->currentDirection = QUIT;
                break;
                default:
                    break;
            }
        }
        return this->currentDirection;
    }

    void Enemy::move(Input direction, Map map) {
        if (map.empty())
            throw quickError(Error::MAP_UNINITIALIZED);
        int x = std::round(this->position.x);
        int y = std::round(this->position.y);
        switch (direction) {
            case UP:
                if (map[y - 1][x] == WALL || std::round(this->position.x) != this->position.x)
                    this->position.y = std::round(this->position.y);
                else
                    this->position.y = this->position.y - this->speed;
            break;
            case DOWN:
                y = this->position.y;
                if (map[y + 1][x] == WALL || std::round(this->position.x) != this->position.x || (x == 10 && y == 7))
                    this->position.y = (int)this->position.y;
                else
                    this->position.y = this->position.y + this->speed;
            break;
            case LEFT:
                if (map[y][x - 1] == WALL || std::round(this->position.y) != this->position.y)
                    this->position.x = std::round(this->position.x);
                else if (x - 1 < 0)
                    this->position.x = map[y].size() - 1;
                else
                    this->position.x = this->position.x - this->speed;
            break;
            case RIGHT:
                x = this->position.x;
                if (map[y][x + 1] == WALL || std::round(this->position.y) != this->position.y)
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
        if (set) {
            this->entityType = ENEMY5;
            this->speed = FLEE_SPEED;
        } else {
            if (this->entityType != ENEMY5_DYING)
                this->entityType = this->type;
            this->speed = CHASE_SPEED;
        }
    }

    void Enemy::kill(std::size_t deltaTime) {
        this->idle = deltaTime;
        this->entityType = ENEMY5_DYING;
    }

    void Enemy::waiting(std::size_t deltaTime) {
        if (this->entityType == ENEMY5_DYING) {
            if (deltaTime > this->idle + 10000) {
                this->entityType = this->type;
                this->idle = 0;
            }
        } else {
            return;
        }
    }

    EntityType Enemy::getType() {
        return this->type;
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

    Bonus::Bonus(Vector2D position, EntityType type)
        : AItem(type, position, 50 * (int)type)
    {}

    Life::Life(Vector2D position)
        : AEntity(PLAYER, position, true)
    {}

    Door::Door()
        : AEntity(WALL, Vector2D(10,8), true)
    {}
}
