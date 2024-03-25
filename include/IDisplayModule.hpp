#pragma once

#include "Type.hpp"

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;

        virtual void display() = 0;
        virtual void clear() = 0;

        virtual std::vector<Input> event() = 0;

        //update must be followed by a display()
        virtual void updateText(const std::string& text, Vector2D pos, bool highlight) = 0;
        virtual void updateEntities(const EntitiesDescription& entities) = 0;
        virtual void updateMap(Map &map) = 0;

        //Display a specific non gameplay screen (splash, game over...)
        virtual void staticScreen(StaticScreen screen) = 0;
        virtual void loadDicts(
                const std::map<EntityType, std::string>& spriteDict,
                const std::map<StaticScreen, std::string>& splashDict) = 0;
};
