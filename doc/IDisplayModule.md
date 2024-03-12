# IDisplayModule

IDisplayModule is an interface which describes a graphical library.

```c++
/*-----Types-----*/

typedef struct LibSelector_s {
    std::vector<std::string>::iterator selected;
    std::vector<std::string> list;
} LibSelector;

typedef struct Menu_s {
    int score;
    std::string name;
    LibSelector graphical;
    LibSelector games;
} Menu;

typedef struct SelectedLib_s {
    std::string graphical;
    std::string game;
} SelectedLib;

typedef struct Vector2D_s {
    std::size_t x;
    std::size_t y;
} Vector2D;

typedef enum EntityType_e {
    WALL = 0,
    PLAYER = 1,
    ...
} EntityType;

typedef struct Map_s {
    std::vector<std::vector<EntityType>> grid;
} Map;

typedef enum Input_e {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    MENU,
    ACTION,
    ...
} Input;

typedef enum Signature_e {
    GAME = 404,
    GRAPHICAL = 808,
} Signature;
```

```c++

/*-----Core-----*/
class IEntity {
    private:
        EntityType entityType;
        Vector2D position;

    public:
        virtual ~IEntity() = 0;
        virtual EntityType getEntityType() = 0;
        virtual void setEntityType(EntityType) = 0;
        virtual Vector2D getPosition() = 0;
        virtual void setPosition(Vector2D position) = 0;ha
};
```

```c++
/*-----Graphical-----*/

class IDisplayModule {
    public:
        ~IDisplayModule() = default;

        virtual void display() = 0;
        virtual void clear() = 0;
        virtual std::vector<Input> event() = 0;
        virtual SelectedLib menu(Menu &menu) = 0;
        virtual void updateText(std::string text, Vector2D pos) = 0; //update must be followed by a display()
        virtual void updateEntity(IEntity &entity) = 0;
        virtual void updateMap(Map &map);
        virtual void staticScreen(std::size_t id) = 0; //Display a specific non gameplay screen (splash, game over...)
        virtual void loadSpriteDict(std::map<EntityType, std::string> spriteDict) = 0;
};

extern "C" {
    IDisplayModule *entryPoint();
    Signature getSignature();
}
```
