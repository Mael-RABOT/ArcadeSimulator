#pragma once

#include <SFML/Graphics.hpp>

#include "IDisplayModule.hpp"

class DisplaySfml : public IDisplayModule {
    private:
        std::map<EntityType, std::string> spriteDict;
        std::map<StaticScreen, std::string> splashDict;
        sf::RenderWindow *window;
        sf::Font font;

    public:
        DisplaySfml();
        ~DisplaySfml();

        void display() override;
        void clear() override;

        std::vector<Input> event() override;

        void updateText(const std::string& text, Vector2D pos, bool highlight) override;
        void updateEntity(IEntity &entity) override;
        void updateMap(Map &map) override;

        void staticScreen(StaticScreen screen) override;
        void loadDicts(
            const std::map<EntityType, std::string>& spriteDict,
            const std::map<StaticScreen, std::string>& splashDict) override;
};