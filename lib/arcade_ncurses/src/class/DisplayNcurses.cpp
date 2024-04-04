#include "DisplayNcurses.hpp"

DisplayNcurses::DisplayNcurses() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

DisplayNcurses::~DisplayNcurses() {
    endwin();
}

void DisplayNcurses::display() {
    refresh();
}

void DisplayNcurses::clear() {
    ::clear();
}

std::vector<Input> DisplayNcurses::event() {
    nodelay(stdscr, TRUE);
    int key = getch();
    std::vector<Input> inputs;
    if (key == ERR)
        return inputs;
    switch (key) {
        case KEY_UP:
            inputs.push_back(UP);
            break;
        case KEY_DOWN:
            inputs.push_back(DOWN);
            break;
        case KEY_LEFT:
            inputs.push_back(LEFT);
            break;
        case KEY_RIGHT:
            inputs.push_back(RIGHT);
            break;
        case 'q':
            inputs.push_back(QUIT);
            break;
        case 'm':
            inputs.push_back(MENU);
            break;
        case ' ':
            inputs.push_back(ACTION);
            break;
        default:
            break;
    }
    return inputs;
}

void DisplayNcurses::updateText(const std::string& text, Vector2D pos, bool highlight) {
    if (highlight)
        attron(A_REVERSE);
    mvprintw(pos.y, pos.x, "%s", text.c_str());
    if (highlight)
        attroff(A_REVERSE);
}

void DisplayNcurses::updateEntities(const EntitiesDescription& entities) {
    for (auto &entity : entities) {
        mvprintw(entity.second.y, entity.second.x, "%s", this->spriteDict[entity.first].first.c_str());
    }
}

void DisplayNcurses::updateMap(Map &map) {
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            mvprintw(y, x, "%s", this->spriteDict[WALL].first.c_str());
        }
    }
}

void DisplayNcurses::staticScreen(StaticScreen screen) {
    ::clear();
}

void DisplayNcurses::loadDicts(
        const std::map<EntityType, std::pair<std::string, std::size_t>>&,
        const std::map<StaticScreen, std::string>&) {
    this->spriteDict = {
            {UNDEFINED, {" ", 1}},
            {WALL, {"#", 1}},
            {PLAYER, {"P", 1}},
            {ENEMY, {"E", 1}},
            {ENEMY1, {"E", 1}},
            {ENEMY2, {"E", 1}},
            {ENEMY3, {"E", 1}},
            {ENEMY4, {"E", 1}},
            {ENEMY5, {"E", 1}},
            {ITEM1, {".", 1}},
            {ITEM2, {"x", 1}},
    };
    this->splashDict = {
            {SCREEN_SPLASH, "Splash"},
            {SCREEN_GAMEOVER, "Game Over"}
    };
}
