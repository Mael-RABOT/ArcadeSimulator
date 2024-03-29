#include "DisplaySfml.hpp"

DisplaySfml::DisplaySfml() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arcade");
    font.loadFromFile("./lib/assets/NotoSansCJK-Regular.ttc");
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
    sf::Event event;
    std::vector<Input> inputs;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                inputs.push_back(Input::QUIT);
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        inputs.push_back(Input::UP);
                        break;
                    case sf::Keyboard::Down:
                        inputs.push_back(Input::DOWN);
                        break;
                    case sf::Keyboard::Left:
                        inputs.push_back(Input::LEFT);
                        break;
                    case sf::Keyboard::Right:
                        inputs.push_back(Input::RIGHT);
                        break;
                    case sf::Keyboard::Escape:
                        inputs.push_back(Input::QUIT);
                        break;
                    case sf::Keyboard::Q:
                        inputs.push_back(Input::QUIT);
                        break;
                    case sf::Keyboard::Space:
                        inputs.push_back(Input::ACTION);
                        break;
                    case sf::Keyboard::M:
                        inputs.push_back(Input::MENU);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return inputs;
}

void DisplaySfml::updateText(const std::string& text, Vector2D pos, bool highlight) {
    sf::RectangleShape background(sf::Vector2f(UNIT_PIXEL_SIZE * 20, UNIT_PIXEL_SIZE + 4));
    background.setPosition(pos.x * (UNIT_PIXEL_SIZE), pos.y * (UNIT_PIXEL_SIZE + 4) + 2);
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(UNIT_PIXEL_SIZE);
    sfText.setPosition(pos.x * (UNIT_PIXEL_SIZE), pos.y * (UNIT_PIXEL_SIZE + 4));
    if (highlight) {
        background.setFillColor(sf::Color::White);
        sfText.setFillColor(sf::Color::Black);
    } else {
        background.setFillColor(sf::Color::Black);
        sfText.setFillColor(sf::Color::White);
    }
    window->draw(background);
    window->draw(sfText);
}

void DisplaySfml::updateEntity(EntityDescription entities) {
    for (auto entity : entities) {
        sf::Texture texture;
        texture.loadFromFile(spriteDict[entity.first].first);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(entity.second.x * UNIT_PIXEL_SIZE, entity.second.y * UNIT_PIXEL_SIZE);
        window->draw(sprite);
    }
}

void DisplaySfml::updateMap(Map &map) {
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            sf::Texture texture;
            texture.loadFromFile(spriteDict[EntityType::WALL].first);
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
        const std::map<EntityType, std::pair<std::string, std::size_t>>& spriteDict,
        const std::map<StaticScreen, std::string>& splashDict) {
    this->spriteDict = spriteDict;
    this->splashDict = splashDict;
}
