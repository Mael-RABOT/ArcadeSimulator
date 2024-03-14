# Type

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

enum EntityType {
    WALL = 0,
    PLAYER = 1,
    ENEMY = 2,
    ITEM1 = 3,
    ITEM2 = 4,
    ITEM3 = 5,
    ITEM4 = 6,
    
};
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

/*-----Core-----*/
class IEntity {
    private:
        EntityType entityType;
        Vector2D position;
        bool visibility;

    public:
        virtual ~IEntity() = 0;
        virtual EntityType getEntityType() = 0;
        virtual void setEntityType(EntityType) = 0;
        virtual Vector2D getPosition() = 0;
        virtual void setPosition(Vector2D position) = 0;
        virtual bool getVisibility() = 0;
        virtual void setVisibility(bool visibility) = 0;
};
```
