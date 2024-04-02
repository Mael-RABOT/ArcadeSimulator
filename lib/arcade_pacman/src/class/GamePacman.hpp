#ifndef PACMAN_GAME_LIB
    #define PACMAN_GAME_LIB

    #include <fstream>
    #include <cstdlib>
    #include <ctime>

    #include "PacmanError.hpp"
    #include "IGameModule.hpp"
    #include "PacmanEntities.hpp"

class GamePacman : public IGameModule {
    private:
        int score = 0;
        pacman::Player player;
        std::vector<pacman::Enemy> listEnemies;
        std::vector<pacman::AItem> listItems;
    public:
        GamePacman();
        ~GamePacman() = default;

        void handleInput(std::size_t deltaTime, Input input) override;
        void update(std::size_t deltaTime) override;

        std::vector<std::string> getInstruction() override;
        EntitiesDescription getEntities() override;

        Map& getMap() override;
        std::map<EntityType, std::pair<std::string, std::size_t>> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;
};

#endif
