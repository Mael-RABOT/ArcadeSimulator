#ifndef PACMAN_GAME_LIB
    #define PACMAN_GAME_LIB

    #include <exception>
    #include <functional>
    #include <fstream>

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
        EntityDescription getEntities() override;

        Map getMap() override;
        std::map<EntityType, std::string> getSpriteDict() override;
        std::map<StaticScreen, std::string> getStaticScreen() override;
};

namespace pacman {
    class Error : public std::exception {
        public:
            typedef enum ErrorType {
                UNKNOWN,
                MAP_NOT_FOUND,
                MAP_CORRUPTED
                MAP_UNINITIALIZED
            } ErrorType_t;

            const char *what(void) const noexcept override;
            void setErrorType(const Error::ErrorType_t type);
        private:
            ErrorType_t _type;
    };

    Error createError(const Error::ErrorType_t type);
}
#endif
