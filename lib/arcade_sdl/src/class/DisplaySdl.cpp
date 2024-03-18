#include "DisplaySdl.hpp"

DisplaySdl::DisplaySdl() {
    window = SDL_CreateWindow("Arcade",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

DisplaySdl::~DisplaySdl() {
    SDL_DestroyWindow(window);
}

void DisplaySdl::display() {
    SDL_RenderPresent(renderer);
}

void DisplaySdl::clear() {
    SDL_RenderClear(renderer);
}

std::vector<Input> DisplaySdl::event() {
    std::vector<Input> inputs;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                inputs.push_back(QUIT);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        inputs.push_back(UP);
                        break;
                    case SDLK_DOWN:
                        inputs.push_back(DOWN);
                        break;
                    case SDLK_LEFT:
                        inputs.push_back(LEFT);
                        break;
                    case SDLK_RIGHT:
                        inputs.push_back(RIGHT);
                        break;
                    case SDLK_q:
                        inputs.push_back(QUIT);
                        break;
                    case SDLK_m:
                        inputs.push_back(MENU);
                        break;
                    case SDLK_SPACE:
                        inputs.push_back(ACTION);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return inputs;
}

void DisplaySdl::updateText(const std::string& text, Vector2D pos, bool highlight) {

}

void DisplaySdl::updateEntity(IEntity &entity) {
    SDL_Rect rect;
    rect.x = entity.getPosition().x;
    rect.y = entity.getPosition().y;
    rect.w = 10;
    rect.h = 10;
    SDL_RenderCopy(renderer, nullptr, nullptr, &rect);
}

void DisplaySdl::updateMap(Map &map) {
}

void DisplaySdl::staticScreen(StaticScreen screen) {
    clear();
}

void DisplaySdl::loadDicts(
        const std::map<EntityType, std::string>& spriteDict,
        const std::map<StaticScreen, std::string>& splashDict) {
    this->spriteDict = spriteDict;
    this->splashDict = splashDict;
}
