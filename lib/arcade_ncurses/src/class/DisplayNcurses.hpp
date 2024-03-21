#pragma once

#include <ncurses.h>

#include "IDisplayModule.hpp"

class DisplayNcurses : public IDisplayModule {
    private:
        std::map<EntityType, std::string> spriteDict;
        std::map<StaticScreen, std::string> splashDict;

    public:
        DisplayNcurses();
        ~DisplayNcurses();

        void display() override;
        void clear() override;

        std::vector<Input> event() override;

        void updateText(const std::string& text, Vector2D pos, bool highlight) override;
        void updateEntity(EntityDescription entities) override;
        void updateMap(Map &map) override;

        void staticScreen(StaticScreen screen) override;
        void loadDicts(
            const std::map<EntityType, std::string>& spriteDict,
            const std::map<StaticScreen, std::string>& splashDict) override;
};
