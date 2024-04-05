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

        if (TTF_Init() == -1) {
            std::string errorMsg = "Error: TTF_Init - ";
            errorMsg += TTF_GetError();
            throw DisplaySdlError(errorMsg);
        }

        font = TTF_OpenFont("./lib/assets/font.ttf", 24);
        if (font == nullptr) {
            std::string errorMsg = "Error: TTF_OpenFont - ";
            errorMsg += TTF_GetError();
            throw DisplaySdlError(errorMsg);
        }
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
    SDL_Color color = {255, 255, 255, 255};
    if (highlight) {
        color = {255, 0, 0, 255};
    }

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surfaceMessage == nullptr) {
        throw DisplaySdlError("Error: TTF_RenderText_Solid");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (message == nullptr) {
        SDL_FreeSurface(surfaceMessage);
        throw DisplaySdlError("Error: SDL_CreateTextureFromSurface");
    }

    SDL_Rect message_rect;
    message_rect.x = pos.x * UNIT_PIXEL_SIZE;
    message_rect.y = pos.y * UNIT_PIXEL_SIZE;
    message_rect.w = surfaceMessage->w;
    message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(renderer, message, NULL, &message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void DisplaySdl::updateEntities(const EntitiesDescription& entities) {
    for (auto &entity : entities) {
        SDL_Surface* surface = IMG_Load(spriteDict[entity.first].first.c_str());
        if (surface == nullptr) {
            throw DisplaySdlError("Error: IMG_Load");
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            SDL_FreeSurface(surface);
            throw DisplaySdlError("Error: SDL_CreateTextureFromSurface");
        }

        SDL_Rect sprite_rect;
        sprite_rect.x = entity.second.x * UNIT_PIXEL_SIZE;
        sprite_rect.y = entity.second.y * UNIT_PIXEL_SIZE;
        sprite_rect.w = surface->w;
        sprite_rect.h = surface->h;

        SDL_RenderCopy(renderer, texture, NULL, &sprite_rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void DisplaySdl::updateMap(Map &map) {
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] == EntityType::WALL) {
                SDL_Surface* surface = IMG_Load(spriteDict[EntityType::WALL].first.c_str());
                if (surface == nullptr) {
                    throw DisplaySdlError("Error: IMG_Load");
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture == nullptr) {
                    SDL_FreeSurface(surface);
                    throw DisplaySdlError("Error: SDL_CreateTextureFromSurface");
                }

                SDL_Rect sprite_rect;
                sprite_rect.x = x * UNIT_PIXEL_SIZE;
                sprite_rect.y = y * UNIT_PIXEL_SIZE;
                sprite_rect.w = surface->w;
                sprite_rect.h = surface->h;

                SDL_RenderCopy(renderer, texture, NULL, &sprite_rect);

                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }
}

void DisplaySdl::staticScreen(StaticScreen screen) {
    clear();
}

void DisplaySdl::loadDicts(
        const std::map<EntityType, std::pair<std::string, std::size_t>>& spriteDict,
        const std::map<StaticScreen, std::string>& splashDict) {
    this->spriteDict = spriteDict;
    this->splashDict = splashDict;
}
