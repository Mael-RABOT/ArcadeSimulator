#pragma once

#include <ncurses.h>

#include "IDisplayModule.hpp"

class DisplayNcurses : public IDisplayModule {
    private:
        std::map<EntityType, std::string> spriteDict;

    public:
        DisplayNcurses();
        ~DisplayNcurses();

        void display() override;
        void clear() override;

        std::vector<Input> event() override;

        void updateText(const std::string& text, Vector2D pos, bool highlight) override;
        void updateEntity(IEntity &entity) override;
        void updateMap(Map &map) override;

        void staticScreen(std::size_t id) override;
        void loadSpriteDict(const std::map<EntityType, std::string>& spriteDict) override;
};
