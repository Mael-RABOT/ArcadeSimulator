#pragma once

#include <vector>
#include <map>
#include <string>
#include <functional>

/*-----Core-----*/

enum KiwiBool {
    NotKiwi = false,
    Kiwi = true
};

struct LibSelector {
    std::vector<std::string>::iterator selected;
    std::vector<std::string> list;
};

struct Menu {
    int score;
    std::string name;
    LibSelector graphical;
    LibSelector game;
};

struct SelectedLib {
    std::string graphical;
    std::string game;
};

struct Vector2D {
    int x;
    int y;

    Vector2D operator+(Vector2D other) const {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-(Vector2D other) const {
        return {x - other.x, y - other.y};
    }

    Vector2D& operator+=(Vector2D other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D& operator-=(Vector2D other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

enum EntityType {
    WALL = 0,
    PLAYER = 1
};

struct Map {
    std::vector<std::vector<EntityType>> grid;
};

enum Input {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    MENU,
    ACTION
};

enum Signature {
    GAME = 404,
    GRAPHICAL = 808,
};

class IEntity {
    private:
        EntityType entityType;
        Vector2D position;

    public:
        virtual ~IEntity() = 0;
        virtual EntityType getEntityType() = 0;
        virtual void setEntityType(EntityType) = 0;
        virtual Vector2D getPosition() = 0;
        virtual void setPosition(Vector2D position) = 0;
};

/*-----Game-----*/

enum GameState {
    RUNNING,
    WIN,
    GAMEOVER,
    SLAPSH
};
