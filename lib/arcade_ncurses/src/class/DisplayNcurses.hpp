#pragma once

#include <ncurses.h>

#include "IDisplayModule.hpp"

class DisplayNcurses : public IDisplayModule {
    private:
        std::map<EntityType, std::pair<std::string, std::size_t>> spriteDict;
        std::map<StaticScreen, std::string> splashDict;

    public:
        DisplayNcurses();
        ~DisplayNcurses();

        void display() override;
        void clear() override;

        std::vector<Input> event() override;

        void updateText(const std::string& text, Vector2D pos, bool highlight) override;
        void updateEntities(const EntitiesDescription& entities) override;
        void updateMap(Map &map) override;

        void staticScreen(StaticScreen screen) override;
        void loadDicts(
            const std::map<EntityType, std::pair<std::string, std::size_t>>& spriteDict,
            const std::map<StaticScreen, std::string>& splashDict) override;
};
