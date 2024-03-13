#pragma once

#include "IDisplayModule.hpp"

class DisplayNcurses : public IDisplayModule {
    public:
        DisplayNcurses();
        ~DisplayNcurses();

        void display() override;
        void clear() override;

        std::vector<Input> event() override;
        SelectedLib menu(Menu &menu) override;

        void updateText(const std::string& text, Vector2D pos) override;
        void updateEntity(IEntity &entity) override;
        void updateMap(Map &map) override;

        void staticScreen(std::size_t id) override;
        void loadSpriteDict(const std::map<EntityType, std::string>& spriteDict) override;
};
