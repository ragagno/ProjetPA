#ifndef PROXIMACENTAURI_GAME_H
#define PROXIMACENTAURI_GAME_H

#include <SDL2/SDL.h>
#include "../model/game/data/Level.h"
#include "../View/View.h"
#include "../model/Model.h"
#include "Controller.h"

const auto TICK_PER_SEC = 60;
const auto MS_PER_UPDATE = 1000. / TICK_PER_SEC;

class GameController
{
public:
    enum State
    {
        TITLE_SCREEN,
        START_GAME,
        OPTIONS,
        IN_GAME,
        _LENGTH
    };
private:
    uint_fast64_t freq;
    uint_fast32_t mapNumber;
    bool looping;
    State state;
    uint_fast32_t *inGameLevel;
    SDL_Window *window;
    Level *maps;
    View *views[State::_LENGTH];
    Model *models[State::_LENGTH];
    Controller *controllers[State::_LENGTH];
public:
    GameController();
    void init();
    ~GameController();
    inline uint_fast64_t getTicks();
    void start();
    void shutdown();
private:
    void loop();
};

#endif //PROXIMACENTAURI_GAME_H