#include "DisplaySfml.hpp"

DisplaySfml::DisplaySfml() {
    sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
    window = new sf::RenderWindow(DesktopMode, "Arcade", sf::Style::Fullscreen);
    font.loadFromFile("./lib/assets/font.ttf");
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
                    case sf::Keyboard::R:
                        inputs.push_back(Input::RESET);
                        break;
                    case sf::Keyboard::D:
                        inputs.push_back(Input::NEXT_DI);
                        break;
                    case sf::Keyboard::G:
                        inputs.push_back(Input::NEXT_GA);
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

void DisplaySfml::updateEntities(const EntitiesDescription& entities) {
    if (this->animeDict.empty()) {
        for (auto sprite : this->spriteDict) {
            this->animeDict.insert({sprite.first, 0});
        }
    }
    for (auto entity : entities) {
        if (entity.first == UNDEFINED)
            continue;
        sf::Texture texture;
        texture.loadFromFile(spriteDict[entity.first].first);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect((this->animeDict[entity.first] / FRAME_RATE_FACTOR) * texture.getSize().y, 0, texture.getSize().y, texture.getSize().y));
        sprite.setScale(UNIT_PIXEL_SIZE / sprite.getGlobalBounds().width, UNIT_PIXEL_SIZE / sprite.getGlobalBounds().height);
        sprite.setPosition(entity.second.x * UNIT_PIXEL_SIZE, entity.second.y * UNIT_PIXEL_SIZE);
        switch (entity.second.rotation) {
            case UP: sprite.setRotation(270); sprite.move(0, UNIT_PIXEL_SIZE); break;
            case DOWN: sprite.setRotation(90); sprite.move(UNIT_PIXEL_SIZE, 0); break;
            case LEFT: sprite.setRotation(180); sprite.move(UNIT_PIXEL_SIZE, UNIT_PIXEL_SIZE); break;
            default: break;
        }
        window->draw(sprite);
        this->animeDict[entity.first]++;
        if (this->animeDict[entity.first] >= spriteDict[entity.first].second * FRAME_RATE_FACTOR)
            this->animeDict[entity.first] = 0;
    }
}

void DisplaySfml::updateMap(Map &map) {
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] != EntityType::UNDEFINED) {
                sf::Texture texture;
                texture.loadFromFile(spriteDict[map[y][x]].first);
                sf::Sprite sprite;
                sprite.setTexture(texture);
                sprite.setScale(UNIT_PIXEL_SIZE / sprite.getGlobalBounds().width, UNIT_PIXEL_SIZE / sprite.getGlobalBounds().height);
                sprite.setPosition(x * UNIT_PIXEL_SIZE, y * UNIT_PIXEL_SIZE);
                window->draw(sprite);
            }
        }
    }
}

void DisplaySfml::staticScreen(StaticScreen screen) {
    clear();
}

void DisplaySfml::loadDicts(
        const std::map<EntityType, std::pair<std::string, std::size_t>>& _spriteDict,
        const std::map<StaticScreen, std::string>& splashDict) {
    this->spriteDict = _spriteDict;
    this->splashDict = splashDict;
}
