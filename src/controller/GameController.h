#ifndef PROXIMACENTAURI_GAME_H
#define PROXIMACENTAURI_GAME_H

#include <SDL2/SDL.h>
#include "../Model/Level.h"
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
        CONTROLS,
        _LENGTH
    };
private:
    unsigned long long freq;
    unsigned int mapNumber;
    bool looping;
    State state;
    SDL_Window *window;
    Level *maps;
    View *views[State::_LENGTH];
    Model *models[State::_LENGTH];
    Controller *controllers[State::_LENGTH];
public:
    GameController();
    ~GameController();
    inline unsigned long long getTicks();
    void init();
    void start();
    void shutdown();
private:
    void loop();
};

#endif //PROXIMACENTAURI_GAME_H