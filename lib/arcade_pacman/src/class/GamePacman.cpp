#include "GamePacman.hpp"

GamePacman::GamePacman()
    : player(pacman::Player()), door(pacman::Door())
{
    this->listEnemies.push_back(pacman::Enemy(Vector2D(9, 9, RIGHT), ENEMY1));
    this->listEnemies.push_back(pacman::Enemy(Vector2D(9, 10, RIGHT), ENEMY2));
    this->listEnemies.push_back(pacman::Enemy(Vector2D(11, 9, LEFT), ENEMY3));
    this->listEnemies.push_back(pacman::Enemy(Vector2D(11, 10, LEFT), ENEMY4));
    for (int i = 0; i < 3; i++)
        this->listLives.push_back(pacman::Life(Vector2D(27 + (2 * i), 2.5)));
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
            if (this->gameState == RUNNING)
                this->player.move(input, this->map);
        break;
        case QUIT:
        case MENU:
            this->instructions.push_back(std::string("loadLibrary lib/arcade_menu.so ") + std::to_string(Signature::GAME));
        break;
        case ACTION:
        break;
    }
}

GameState GamePacman::computeState() {
    if (this->lives <= 0)
        return GAMEOVER;
    bool isWin = true;
    for (auto item : this->listItems) {
        isWin = isWin && (item.getEntityType() != ITEM1);
    }
    if (isWin)
        return WIN;
    return RUNNING;
}

void GamePacman::update(std::size_t deltaTime) {
    if (this->map.empty())
        throw pacman::quickError(pacman::Error::MAP_UNINITIALIZED);
    if (this->entities.empty())
        throw pacman::quickError(pacman::Error::ENTITIES_UNINITIALIZED);
    if (!this->instructions.empty())
        this->instructions.clear();
    this->gameState = this->computeState();
    this->instructions.push_back(std::string("displayText STATE 22 4 false"));
    switch (this->gameState) {
        case RUNNING:
            this->instructions.push_back(std::string("displayText RUNNING 27 4 false"));
        break;
        case WIN:
            this->instructions.push_back(std::string("displayText WIN 27 4 false"));
            return;
        break;
        case GAMEOVER:
            this->instructions.push_back(std::string("displayText GAME 27 4 false"));
            this->instructions.push_back(std::string("displayText OVER 31 4 false"));
            return;
        break;
        default:
            throw pacman::quickError(pacman::Error::GAME_CRASH);
    }
    
    if (this->gameState != RUNNING) {
        
        return;
    } 
    this->player.waiting();
    for (std::vector<pacman::AItem>::iterator i = this->listItems.begin(); i != this->listItems.end(); i++) {
        if (std::round(this->player.getPosition().x) == i->getPosition().x && std::round(this->player.getPosition().y) == i->getPosition().y) {
            if (i->getVisibility()) {
                this->score += i->getPoints();
                i->setVisibility(false);
                if (i->getEntityType() == ITEM2)
                    this->endEffect = deltaTime + 10000;
                i->setEntityType(UNDEFINED);
            }
        }
    }
    if (deltaTime > 10000)
        this->openDoor();
    std::size_t index = 0;
    for (std::vector<pacman::Enemy>::iterator i = this->listEnemies.begin(); i != this->listEnemies.end(); i++) {
        i->vulnerable(deltaTime < this->endEffect);
        Input direction = QUIT;
        if (deltaTime > 10000 * (index + 1))
            direction = i->chooseDirection(this->player, this->map);
        i->move(direction, this->map);
        if (std::round(this->player.getPosition().x) == i->getPosition().x && std::round(this->player.getPosition().y) == i->getPosition().y) {
            this->player.kill();
            this->lives--;
            if (this->lives >= 0)
                this->listLives[this->lives].setVisibility(false);
        }
        index++;
    }
    this->instructions.push_back(std::string("displayText SCORE 22 0 false"));
    this->instructions.push_back(std::string("displayText ") + std::to_string(this->score) + std::string(" 28 0 false"));
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
    this->entities.push_back(std::ref(this->door));
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
    int nGum = 0;
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
                this->listItems.push_back((pacman::AItem)(pacman::Pacdot(Vector2D(x, y))));
            } else if (*c == '!') {
                mapLine.push_back(UNDEFINED);
            } else if (*c != '\n') {
                throw pacman::quickError(pacman::Error::MAP_CORRUPTED);
            }
            x++;
        }
        this->map.push_back(mapLine);
        y++;
    }
    mapFile.close();
    while (nGum < 4) {
        int i = 0;
        for (auto item : this->listItems) {
            if (std::rand() % 45 == 0 && nGum < 4 && item.getEntityType() != ITEM2) {
                this->listItems[i] = (pacman::AItem)(pacman::Pacgum(item.getPosition()));
                nGum++;
            }
            i++;
        }
    }
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

void GamePacman::openDoor() {
    this->door.setVisibility(false);
}
