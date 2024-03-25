#include "DisplaySdl.hpp"

DisplaySdl::DisplaySdl() {
    try {
        window = SDL_CreateWindow("Arcade",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  800, 600, 0);
        if (window == nullptr) throw DisplaySdlError("Error: SDL_CreateWindow");
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == nullptr) throw DisplaySdlError("Error: SDL_CreateRenderer");
        font = TTF_OpenFont("./lib/assets/NotoSansCJK-Regular.ttc", 24);
        if (font == nullptr) throw DisplaySdlError("Error: TTF_OpenFont");
    } catch (...) {
        SDL_DestroyWindow(window);
        throw;
    }
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
//    SDL_Event event;
//    while (SDL_PollEvent(&event)) {
//        switch (event.type) {
//            case SDL_QUIT:
//                inputs.push_back(QUIT);
//                break;
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym) {
//                    case SDLK_UP:
//                        inputs.push_back(UP);
//                        break;
//                    case SDLK_DOWN:
//                        inputs.push_back(DOWN);
//                        break;
//                    case SDLK_LEFT:
//                        inputs.push_back(LEFT);
//                        break;
//                    case SDLK_RIGHT:
//                        inputs.push_back(RIGHT);
//                        break;
//                    case SDLK_q:
//                        inputs.push_back(QUIT);
//                        break;
//                    case SDLK_m:
//                        inputs.push_back(MENU);
//                        break;
//                    case SDLK_SPACE:
//                        inputs.push_back(ACTION);
//                        break;
//                    default:
//                        break;
//                }
//                break;
//            default:
//                break;
//        }
//    }
    return inputs;
}

void DisplaySdl::updateText(const std::string& text, Vector2D pos, bool highlight) {
    SDL_Color color = highlight ? SDL_Color{255, 255, 255, 255} : SDL_Color{127, 127, 127, 255}; // white if highlighted, gray otherwise
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        this->~DisplaySdl();
        throw DisplaySdlError("Error: TTF_RenderText_Solid");
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_FreeSurface(surface);
        this->~DisplaySdl();
        throw DisplaySdlError("Error: SDL_CreateTextureFromSurface");
    }

    SDL_Rect rect;
    rect.x = pos.x;
    rect.y = pos.y;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h); // get the width and height of the texture

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void DisplaySdl::updateEntities(const EntitiesDescription& entities) {
    for (auto &entity : entities) {
        (void)entity;
    }
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
