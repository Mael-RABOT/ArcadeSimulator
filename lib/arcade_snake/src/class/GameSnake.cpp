#include "GameSnake.hpp"

GameSnake::GameSnake()
{
    _state = GameState::RUNNING;
    _score = 0;
    _live = 3;
    direction.x = 1;
    direction.y = 0;
    initPlayer();
    Map map(32, std::vector<EntityType>(32, EntityType::UNDEFINED));

    for(int i = 0; i < 32; map[0][i]=map[31][i]=map[i][0]=map[i][31]=EntityType::WALL, i++)
        if (i > 0 && i < 31) map[i][0]=map[i][31]=EntityType::WALL;

    this->map = map;
    spawnApple();
}

GameSnake::~GameSnake() {}

void GameSnake::turn(bool trigonometric) {
    std::map<std::pair<int, int>, std::pair<int, int>> directionMap = {
            {{0, -1}, {-1, 0}},
            {{1, 0}, {0, -1}},
            {{0, 1}, {1, 0}},
            {{-1, 0}, {0, 1}}
    };

    std::pair<int, int> newDirection = trigonometric ? directionMap[{direction.x, direction.y}] : directionMap[{-direction.x, -direction.y}];
    direction.x = newDirection.first;
    direction.y = newDirection.second;
}

void GameSnake::handleInput(std::size_t deltaTime, Input input) {
    switch (input) {
        case LEFT:
            turn(true);
            break;
        case RIGHT:
            turn(false);
            break;
        default:
            break;
    }
}

void GameSnake::update(std::size_t deltaTime) {
    movePlayer();
}

std::vector <std::string> GameSnake::getInstruction() {
    return std::vector<std::string>();
}

EntitiesDescription GameSnake::getEntities() {
    if (_state == GAMEOVER)
        return EntitiesDescription();

    EntitiesDescription ents;
    for (auto entity : this->player) {
        entity.getEntityType();
        ents.push_back({entity.getEntityType(), entity.getPosition()});
    }
    ents.push_back({EntityType::ITEM1, applePos});
    return ents;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GameSnake::getSpriteDict() {
    std::map<EntityType, std::pair<std::string, std::size_t>> dict = {
        {EntityType::PLAYER, {std::string("lib/assets/snake_gentitler.png"), 0}},
        {EntityType::PLAYER_SEC, {std::string("lib/assets/snake_body.png"), 0}},
        {EntityType::ITEM1, {std::string("lib/assets/snake_apple.png"), 0}},
        {EntityType::WALL, {std::string("lib/assets/snake_wall.png"), 0}},
    };
    return dict;
}

std::map <StaticScreen, std::string> GameSnake::getStaticScreen() {
    return std::map<StaticScreen, std::string>();
}

Map& GameSnake::getMap() {
    return this->map;
}

void GameSnake::initPlayer()
{
    PlayerElement head;
    head.setEntityType(PLAYER);
    head.setPosition({7.0f, 7.0f});
    player.push_back(head);

    for (int i = 0; i < 3; i++) {
        PlayerElement bodyCell;
        bodyCell.setEntityType(PLAYER_SEC);
        bodyCell.setPosition({7.0f - i + 1, 7.0f});
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
                Map map(32, std::vector<EntityType>(32, EntityType::WALL));
                this->map = map;
                return;
            }
            player.at(i).setPosition(futurePos);
            return;
        }
        player.at(i).setPosition(player.at(i - 1).getPosition());
        i--;
    }
}

void GameSnake::spawnApple() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 30);

    bool isOccupied = true;
    while (isOccupied) {
        int x = distrib(gen);
        int y = distrib(gen);

        isOccupied = false;
        for (const auto& part : player) {
            if (part.getPosition().x == x && part.getPosition().y == y) {
                isOccupied = true;
                break;
            }
        }

        if (!isOccupied) {
            applePos.x = x;
            applePos.y = y;
        }
    }
}

bool GameSnake::collide()
{
    Vector2D headPos = player.at(0).getPosition();
    headPos += direction;

    for (std::size_t i = 0; i < this->map.size(); i++) {
        for (std::size_t j = 0; j < this->map[i].size(); j++) {
            if (this->map[i][j] == EntityType::WALL) {
                if (headPos.x == j && headPos.y == i) {
                    return true;
                }
            }
            if (this->map[i][j] == EntityType::PLAYER_SEC) {
                if (headPos.x == j && headPos.y == i) {
                    return true;
                }
            }
        }
    }

    if (headPos.x == applePos.x && headPos.y == applePos.y) {
        PlayerElement bodyCell;
        bodyCell.setEntityType(PLAYER_SEC);
        bodyCell.setPosition(player.at(player.size() - 1).getPosition());
        player.push_back(bodyCell);
        spawnApple();
    }

    return false;
}
