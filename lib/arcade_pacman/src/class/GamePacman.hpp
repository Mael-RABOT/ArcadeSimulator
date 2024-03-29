#ifndef PACMAN_GAME_LIB
    #define PACMAN_GAME_LIB

    #include <fstream>

    #include "ArcadeException.hpp"
    #include "IGameModule.hpp"

class GamePacman : public IGameModule {
    private:
        int score = 0;
    public:
        GamePacman() = default;
        ~GamePacman() = default;

        void handleInput(std::size_t deltaTime, Input input) override;
        void update(std::size_t deltaTime) override;

        std::vector<std::string> getInstruction() override;
        EntitiesDescription getEntities() override;

        Map getMap() override;
        std::map<EntityType, std::pair<std::string, std::size_t>> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;
};

namespace pacman {
    class Error : public ArcadeException {
        public:
            typedef enum ErrorType {
                UNKNOWN,
                MAP_NOT_FOUND,
                MAP_CORRUPTED,
                MAP_UNINITIALIZED
            } ErrorType_t;

            Error(const std::string &message) : ArcadeException(message) {};
    };

    Error quickError(const Error::ErrorType_t type);
}
#endif
