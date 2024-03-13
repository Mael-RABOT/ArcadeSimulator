#pragma once

#include <vector>
#include <map>
#include <string>

typedef struct LibSelector_s {
    std::vector<std::string>::iterator selected;
    std::vector<std::string> list;
} LibSelector;

typedef struct Menu_s {
    int score;
    std::string name;
    LibSelector graphical;
    LibSelector games;
} Menu;

typedef struct SelectedLib_s {
    std::string graphical;
    std::string game;
} SelectedLib;

typedef struct Vector2D_s {
    std::size_t x;
    std::size_t y;
} Vector2D;

typedef enum EntityType_e {
    WALL = 0,
    PLAYER = 1
} EntityType;

typedef struct Map_s {
    std::vector<std::vector<EntityType>> grid;
} Map;

typedef enum Input_e {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    MENU,
    ACTION
} Input;

typedef enum Signature_e {
    GAME = 404,
    GRAPHICAL = 808,
} Signature;

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

typedef enum GameState_e {
    RUNNING,
    WIN,
    GAMEOVER,
    SLAPSH
} GameState;
