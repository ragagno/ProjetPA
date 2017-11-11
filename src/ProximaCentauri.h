#ifndef PROXIMACENTAURI_PROXIMACENTAURI_H
#define PROXIMACENTAURI_PROXIMACENTAURI_H

#include <SDL2/SDL_timer.h>
#include "controller/Controller.h"
#include "model/game/map/Map.h"

// FPS constants
const auto TARGET_FPS = 60u;
const auto TARGET_MS_PER_FRAME = 1000u / TARGET_FPS;
// TPS constants
const auto TARGET_TPS = 60u;
const auto TARGET_MS_PER_TICK = 1000u / TARGET_TPS;
// WINDOW constants
const auto WINDOW_TITLE = "Proxima Centauri";
const auto WINDOW_WIDTH = 720u;
const auto WINDOW_HEIGHT = 960u;
// FONT 144 constants
const auto SDL_ttfDumbTopMargin_144 = 7u;
const auto SDL_ttfDumbBottomMargin_144 = 31u;
const auto SDL_ttfDumbRightMargin_144 = 14u;
const auto SDL_ttfDumbLeftMargin_144 = 0u;
// FONT 64 constants
const auto SDL_ttfDumbTopMargin_64 = 3u;
const auto SDL_ttfDumbBottomMargin_64 = 14u;
const auto SDL_ttfDumbRightMargin_64 = 6u;
const auto SDL_ttfDumbLeftMargin_64 = 0u;
// UNDERLINE constants
const auto UNDERLINE_THICKNESS = 6u;
const auto UNDERLINE_SPACING = 6u;
// FONT constants
const auto SPACE_WIDTH = 25u;
// SPRITES constants
const auto TICK_PER_SPRITE_SPACESHIP = 8u;
const auto TICK_PER_SPRITE_BACKGROUND = 1u;
// MENU constats
const auto MENU_SPACEING = 50u;

class ProximaCentauri
{
public:
    enum GameState
    {
        TITLE_SCREEN,
        MAP_SELECTION,
        OPTIONS,
        IN_GAME,
        _LENGTH
    };
private:
    bool initialized;
    bool looping;
    bool paused;
    uint_fast32_t currentMap;
    uint_fast32_t mapNumber;
    uint_fast32_t backgroundOffset;
    GameState state;
    Map *maps;
    SDL_Texture *starBackground;
    SDL_Texture *spaceshipSprite;
    SDL_Texture *upArrow;
    SDL_Texture *downArrow;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Controller *controllers[_LENGTH];
public:
    static ProximaCentauri *getInstance();
    void init();
    uint_fast32_t getMapNumber() const;
    uint_fast32_t getBackgroundOffset() const;
    Map *getMaps() const;
    const Map getCurrentMap() const;
    SDL_Texture *getStarBackground() const;
    SDL_Texture *getSpaceshipSprite() const;
    SDL_Texture *getUpArrow() const;
    SDL_Texture *getDownArrow() const;
    void setPaused(bool paused);
    void setState(GameState state);
    void setCurrentMap(uint_fast32_t index);
    void stopGame();
    void start();
    void shutdown();
private:
    ProximaCentauri();
    ProximaCentauri(const ProximaCentauri &initial);
    const ProximaCentauri &operator=(const ProximaCentauri &initial);
    ~ProximaCentauri() = default;
    void loop();

    uint_fast64_t getTicksFromStart()
    {
        static auto freq = SDL_GetPerformanceFrequency() / 1000;
        return SDL_GetPerformanceCounter() / freq;
    }

    uint_fast64_t getTicks()
    {
        static auto startTime = getTicksFromStart();
        return getTicksFromStart() - startTime;
    }
};

#endif //PROXIMACENTAURI_PROXIMACENTAURI_H