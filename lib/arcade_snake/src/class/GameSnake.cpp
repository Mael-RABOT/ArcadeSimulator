#include "GameSnake.hpp"

GameSnake::GameSnake()
{
    _state = GameState::RUNNING;
    _score = 0;
    _live = 3;
    direction.x = 1;
    direction.y = 0;
    initMap();
}

GameSnake::GameSnake() {}
GameSnake::~GameSnake() {}

void GameSnake::handleInput(std::size_t deltaTime, Input input)
{
    if (input == UP) {
        direction.x = 0;
        direction.y = -1;
        return;
    }
    if (input == DOWN) {
        direction.x = 0;
        direction.y = 1;
        return;
    }
    if (input == LEFT) {
        direction.x = -1;
        direction.y = 0;
        return;
    }
    if (input == RIGHT) {
        direction.x = 1;
        direction.y = 0;
    }
}

void GameSnake::update(std::size_t deltaTime)
{
    for (std::size_t entityI; std::reference_wrapper<IEntity> entity : entities) {
        IEntity& current = entity.get();
        if (current.getEntityType() == PLAYER) {
            current.setPosition(current.getPosition() += direction);
        }
    }
}

std::vector <std::string> GameSnake::getInstruction()
{
    return std::vector<std::string>();
}

EntitiesDescription GameSnake::getEntities()
{
    EntitiesDescription entities;
    return entities;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameSnake::getSpriteDict()
{
    return std::map<EntityType, std::pair<std::string, std::size_t>>();
}

std::map <StaticScreen, std::string> GameSnake::getStaticScreen()
{
    return std::map<StaticScreen, std::string>();
}

Map& GameSnake::getMap()
{
    return this->map;
}

void GameSnake::initMap() {
    for (int i = 0; i < 16; i++) {
        map.push_back({});
        for (int j = 0; j < 16; j++) {
            map[i].push_back(UNDEFINED);
        }
    }
}

void GameSnake::initPlayer() {
    PlayerElement head;
    head.setEntityType(PLAYER);
    std::reference_wrapper current {head};
    player.push_back(current);

    for (int i = 0; i < 4; i++) {
        PlayerElement bodyCell;
        bodyCell.setEntityType(PLAYER_SEC);
        current = std::reference_wrapper {bodyCell};
        player.push_back(current);
    }
}
