#include "DisplayNcurses.hpp"

DisplayNcurses::DisplayNcurses() {}

DisplayNcurses::~DisplayNcurses() {}

void DisplayNcurses::display() {}

void DisplayNcurses::clear() {}

std::vector<Input> DisplayNcurses::event() {
    return std::vector<Input>();
}

SelectedLib DisplayNcurses::menu(Menu &menu) {
    return {"", ""};
}

void DisplayNcurses::updateText(const std::string& text, Vector2D pos) {}

void DisplayNcurses::updateEntity(IEntity &entity) {}

void DisplayNcurses::updateMap(Map &map) {}

void DisplayNcurses::staticScreen(std::size_t id) {}

void DisplayNcurses::loadSpriteDict(const std::map<EntityType, std::string>& spriteDict) {}
