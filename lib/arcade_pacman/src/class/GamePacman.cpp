#include "GamePacman.hpp"

GamePacman::GamePacman()
    : player(pacman::Player())
{}

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
    this->player.waiting();
    for (std::vector<pacman::AItem>::iterator i = this->listItems.begin(); i != this->listItems.end(); i++) {
        if (this->player.getPosition().x == i->getPosition().x && this->player.getPosition().y == i->getPosition().y) {
            i->setVisibility(false);
        }
    }
}

std::vector<std::string> GamePacman::getInstruction() {
    std::vector<std::string> list = {std::string("")};
    return list;
}

EntitiesDescription GamePacman::getEntities() {
    if (!this->entitiesDescriptor.empty())
        this->entitiesDescriptor.clear();
    if (!this->entities.empty())
        this->entities.clear();
    for (std::vector<pacman::AItem>::iterator i = this->listItems.begin(); i != this->listItems.end(); i++) {
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
        {EntityType::ITEM7, {std::string("lib/assets/pacman_item7.png"), 0}}
    };
    return dict;
}

std::map<StaticScreen, std::string> GamePacman::getStaticScreen() {
    std::map<StaticScreen, std::string> dict = {
    };
    return dict;
}
