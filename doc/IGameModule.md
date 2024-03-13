# IGameModule

The game module is the part of the program that will handle the game logic. It will be loaded at runtime by the core of the program.

```c++
/*-----Game-----*/

// std::vector<std::reference_wrapper<Entity>> reference(entity)
// std::vector<std::pair<std::string, Vector2D>> texts = {{"text", {x, y}}}

typedef enum GameState_e {
    RUNNING,
    WIN,
    GAMEOVER,
    SLAPSH
} GameState;

class IGameModule {
    public:
        ~IGameModule() = default;
        
        virtual std::size_t getScore() = 0;
        virtual GameState getState() = 0;
        virtual std::size_t getLive() = 0;
        virtual void handleInput(std::size_t deltaTime, Input input, const std::unordered_map<std::size_t, std::reference_wrapper<IEntity>>& entities) = 0;
        virtual void update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) = 0; //delta since the start of the game
        virtual std::vector<std::pair<std::string, Vector2D>> getTexts() = 0;
        virtual std::vector<std::reference_wrapper<IEntity>> initEntities(Map &map) = 0;
};

extern "C" {
    IGameModule *entryPoint();
    Signature getSignature();
}
```
