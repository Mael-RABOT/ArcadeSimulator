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
        virtual std::size_t getScore() = 0;
        virtual GameState getState() = 0;
        virtual std::size_t getLive() = 0;
        
        //delta since the start of the game
        virtual void handleInput(std::size_t deltaTime, Input input, const std::vector<std::reference_wrapper<IEntity>>& entities) = 0;
        virtual void update(std::size_t deltaTime, const std::vector<std::reference_wrapper<IEntity>>& entities) = 0;
        
        //return an instruction sent from the game to the core, see the documentation for more details
        virtual std::vector<std::string> getInstruction() = 0;
        
        //init function to call on game start
        virtual std::vector<std::reference_wrapper<IEntity>> initEntities(Map &map) = 0;
        virtual std::map<EntityType, std::string> getSpriteDict() = 0;
};


extern "C" {
    IGameModule *entryPoint();
    Signature getSignature();
}
```
