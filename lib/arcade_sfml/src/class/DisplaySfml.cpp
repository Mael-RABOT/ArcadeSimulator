#include "DisplaySfml.hpp"

DisplaySfml::DisplaySfml() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arcade");
    font.loadFromFile("./lib/assets/NotoSansCJK-Regular.ttf");
}

DisplaySfml::~DisplaySfml() {
    delete window;
}

void DisplaySfml::display() {
    window->display();
}

void DisplaySfml::clear() {
    window->clear();
}

std::vector<Input> DisplaySfml::event() {
    std::vector<Input> inputs;
    return inputs;
}

void DisplaySfml::updateText(const std::string& text, Vector2D pos, bool highlight) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(24);
    sfText.setFillColor(sf::Color::White);
    sfText.setPosition(pos.x, pos.y);
    window->draw(sfText);
}

void DisplaySfml::updateEntity(IEntity &entity) {
    sf::Texture texture;
    texture.loadFromFile(spriteDict[entity.getEntityType()]);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
    window->draw(sprite);
}

void DisplaySfml::updateMap(Map &map) {
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            sf::Texture texture;
            texture.loadFromFile(spriteDict[EntityType::WALL]);
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition(x, y);
            window->draw(sprite);
        }
    }
}

void DisplaySfml::staticScreen(StaticScreen screen) {
    clear();
}

void DisplaySfml::loadDicts(
        const std::map<EntityType, std::string>& spriteDict,
        const std::map<StaticScreen, std::string>& splashDict) {
    this->spriteDict = spriteDict;
    this->splashDict = splashDict;
}
