#include "GameSnake.hpp"

GameSnake::GameSnake()
{
    _state = GameState::RUNNING;
    _score = 0;
    _live = 3;
    direction.x = 1;
    direction.y = 0;
    initPlayer();
}

GameSnake::~GameSnake() {}

void GameSnake::turnLeft()
{
    if (direction.x == 0 && direction.y == -1) {
        direction.x = -1;
        direction.y = 0;
        return;
    }
    if (direction.x == 1 && direction.y == 0) {
        direction.x = 0;
        direction.y = -1;
        return;
    }
    if (direction.x == 0 && direction.y == 1) {
        direction.x = 1;
        direction.y = 0;
        return;
    }
    if (direction.x == -1 && direction.y == 0) {
        direction.x = 0;
        direction.y = 1;
    }
}

void GameSnake::turnRight()
{
    if (direction.x == 0 && direction.y == -1) {
        direction.x = 1;
        direction.y = 0;
        return;
    }
    if (direction.x == 1 && direction.y == 0) {
        direction.x = 0;
        direction.y = 1;
        return;
    }
    if (direction.x == 0 && direction.y == 1) {
        direction.x = -1;
        direction.y = 0;
        return;
    }
    if (direction.x == -1 && direction.y == 0) {
        direction.x = 0;
        direction.y = - 1;
    }
}

void GameSnake::handleInput(std::size_t deltaTime, Input input)
{
    if (input == LEFT) {
        turnLeft();
        return;
    }
    if (input == RIGHT) {
        turnRight();
    }
}

void GameSnake::update(std::size_t deltaTime)
{
    movePlayer();
}

std::vector <std::string> GameSnake::getInstruction()
{
    return std::vector<std::string>();
}

EntitiesDescription GameSnake::getEntities()
{
    EntitiesDescription ents;
    for (auto entity : this->player) {
        entity.getEntityType();
        ents.push_back({entity.getEntityType(), entity.getPosition()});
    }
    return ents;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameSnake::getSpriteDict()
{
    std::map<EntityType, std::pair<std::string, std::size_t>> dict = {
        {EntityType::PLAYER, {std::string("lib/assets/snake_gentitler.png"), 0}},
        {EntityType::PLAYER_SEC, {std::string("lib/assets/snake_body.png"), 0}},
        {EntityType::ITEM1, {std::string("lib/assets/snake_apple.png"), 0}}
    };
    return dict;
}

std::map <StaticScreen, std::string> GameSnake::getStaticScreen()
{
    return std::map<StaticScreen, std::string>();
}

Map& GameSnake::getMap()
{
    return this->map;
}

void GameSnake::initPlayer()
{
    PlayerElement head;
    head.setEntityType(PLAYER);
    head.setPosition({7, 7});
    player.push_back(head);

    for (int i = 0; i < 3; i++) {
        PlayerElement bodyCell;
        bodyCell.setEntityType(PLAYER_SEC);
        bodyCell.setPosition({7 - i + 1, 7});
        player.push_back(bodyCell);
    }
}

void GameSnake::movePlayer()
{
    int i = player.size() - 1;
    Vector2D futurePos = player.at(0).getPosition();
    futurePos.x += direction.x;
    futurePos.y += direction.y;

    while (i >= 0) {
        if (i == 0) {
            if (collide()) {
                _state = GAMEOVER;
                return;
            }
            player.at(i).setPosition(futurePos);
            return;
        }
        player.at(i).setPosition(player.at(i - 1).getPosition());
        i--;
    }
}

bool GameSnake::collide()
{
    Vector2D futurePos = player.at(0).getPosition();
    futurePos.x += direction.x;
    futurePos.y += direction.y;

    if (futurePos.x < 0 || futurePos.x > 31) {
        return true;
    }
    if (futurePos.y < 0 || futurePos.y > 31) {
        return true;
    }

    int i = player.size() - 1;

    while (i > 0) {
        if (futurePos == player.at(i).getPosition()) {
            return true;
        }
        i--;
    }
    return false;
}
