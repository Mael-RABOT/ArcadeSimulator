#include "GamePacman.hpp"

GamePacman::GamePacman()
    : player(pacman::Player())
{
    this->listEnemies.push_back(pacman::RedGhost());
    this->listEnemies.push_back(pacman::OrangeGhost());
    this->listEnemies.push_back(pacman::BlueGhost());
    this->listEnemies.push_back(pacman::PinkGhost());
    for (int i = 0; i < 3; i++)
        this->listLives.push_back(pacman::Life(Vector2D(26 + (2 * i), 2.5)));
}

void GamePacman::handleInput(std::size_t deltaTime, Input input) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
    if (this->entities.empty())
        throw pacman::quickError(pacman::Error::ENTITIES_UNINITIALIZED);
    switch (input) {
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            this->player.move(input, this->map);
        break;
        case QUIT:
        break;
        case MENU:
        break;
        case ACTION:
            this->player.kill();
        break;
    }
}

void GamePacman::update(std::size_t deltaTime) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
    if (this->entities.empty())
        throw pacman::quickError(pacman::Error::ENTITIES_UNINITIALIZED);
    this->instructions.clear();
    this->player.waiting();
    for (std::vector<pacman::AItem>::iterator i = this->listItems.begin(); i != this->listItems.end(); i++) {
        if (std::round(this->player.getPosition().x) == i->getPosition().x && std::round(this->player.getPosition().y) == i->getPosition().y) {
            if (i->getVisibility()) {
                this->score += i->getPoints();
                i->setVisibility(false);
            }
        }
    }
    for (std::vector<pacman::Enemy>::iterator i = this->listEnemies.begin(); i != this->listEnemies.end(); i++) {
        //i->move(i->chooseDirection(this->player, this->map), this->map);
        if (std::round(this->player.getPosition().x) == i->getPosition().x && std::round(this->player.getPosition().y) == i->getPosition().y) {
            this->player.kill();
            this->lives--;
            if (this->lives >= 0)
                this->listLives[this->lives].setVisibility(false);
        }
    }
    this->instructions.push_back(std::string("displayText SCORE 22 0 false"));
    this->instructions.push_back(std::string("displayText ") + std::to_string(this->score) + std::string(" 26 0 false"));
    this->instructions.push_back(std::string("displayText LIVES 22 2 false"));
}

std::vector<std::string> GamePacman::getInstruction() {
    return this->instructions;
}

EntitiesDescription GamePacman::getEntities() {
    if (!this->entitiesDescriptor.empty())
        this->entitiesDescriptor.clear();
    if (!this->entities.empty())
        this->entities.clear();
    for (std::vector<pacman::AItem>::iterator i = this->listItems.begin(); i != this->listItems.end(); i++) {
        this->entities.push_back(std::ref(*i));
    }
    for (std::vector<pacman::Enemy>::iterator i = this->listEnemies.begin(); i != this->listEnemies.end(); i++) {
        this->entities.push_back(std::ref(*i));
    }
    for (std::vector<pacman::Life>::iterator i = this->listLives.begin(); i != this->listLives.end(); i++) {
        this->entities.push_back(std::ref(*i));
    }
    this->entities.push_back(std::ref(this->player));
    for (std::vector<std::reference_wrapper<IEntity>>::iterator i = this->entities.begin(); i != this->entities.end(); i++) {
        if (i->get().getVisibility())
            this->entitiesDescriptor.push_back(std::pair(i->get().getEntityType(), i->get().getPosition()));
    }
    return this->entitiesDescriptor;
}

Map& GamePacman::getMap() {
    if (!this->map.empty())
        return this->map;
    std::ifstream mapFile;
    mapFile.open ("lib/assets/pacman_map.txt");
    if (!mapFile.is_open()) {
        throw pacman::quickError(pacman::Error::MAP_NOT_FOUND);
    }
    std::srand(std::time(nullptr));
    std::string line;
    int y = 0;
    while(std::getline(mapFile, line)) {
        if (!this->map.empty() && this->map[y - 1].size() != line.length()) {
            throw pacman::quickError(pacman::Error::MAP_CORRUPTED);
        }
        std::vector<EntityType> mapLine;
        int x = 0;
        for (std::string::iterator c = line.begin(); c != line.end(); c++) {
            if (*c == '#') {
                mapLine.push_back(WALL);
            } else if (*c == ' ') {
                mapLine.push_back(UNDEFINED);
                this->listItems.push_back((std::rand() % 15 == 0) ? (pacman::AItem)(pacman::Pacgum(Vector2D(x, y))) : (pacman::AItem)(pacman::Pacdot(Vector2D(x, y))));
            } else if (*c != '\n') {
                throw pacman::quickError(pacman::Error::MAP_CORRUPTED);
            }
            x++;
        }
        this->map.push_back(mapLine);
        y++;
    }
    mapFile.close();
    return this->map;
}

std::map<EntityType, std::pair<std::string, std::size_t>> GamePacman::getSpriteDict() {
    std::map<EntityType, std::pair<std::string, std::size_t>> dict = {
        {EntityType::WALL, {std::string("lib/assets/pacman_wall.png"), 0}},
        {EntityType::PLAYER, {std::string("lib/assets/pacman_player.png"), 0}},
        {EntityType::PLAYER_MOVE, {std::string("lib/assets/pacman_player_move.png"), 4}},
        {EntityType::PLAYER_DYING, {std::string("lib/assets/pacman_player_dying.png"), 9}},
        {EntityType::ITEM1, {std::string("lib/assets/pacman_item1.png"), 0}},
        {EntityType::ITEM2, {std::string("lib/assets/pacman_item2.png"), 0}},
        {EntityType::ITEM3, {std::string("lib/assets/pacman_item3.png"), 0}},
        {EntityType::ITEM4, {std::string("lib/assets/pacman_item4.png"), 0}},
        {EntityType::ITEM5, {std::string("lib/assets/pacman_item5.png"), 0}},
        {EntityType::ITEM6, {std::string("lib/assets/pacman_item6.png"), 0}},
        {EntityType::ITEM7, {std::string("lib/assets/pacman_item7.png"), 0}},
        {EntityType::ENEMY1, {std::string("lib/assets/pacman_enemy1.png"), 2}},
        {EntityType::ENEMY2, {std::string("lib/assets/pacman_enemy2.png"), 2}},
        {EntityType::ENEMY3, {std::string("lib/assets/pacman_enemy3.png"), 2}},
        {EntityType::ENEMY4, {std::string("lib/assets/pacman_enemy4.png"), 2}},
        {EntityType::ENEMY5, {std::string("lib/assets/pacman_enemy5.png"), 2}}
    };
    return dict;
}

std::map<StaticScreen, std::string> GamePacman::getStaticScreen() {
    std::map<StaticScreen, std::string> dict = {
    };
    return dict;
}
