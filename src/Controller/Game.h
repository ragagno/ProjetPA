#ifndef PROXIMACENTAURI_GAME_H
#define PROXIMACENTAURI_GAME_H

#include <SDL2/SDL.h>
#include "../Model/Level.h"
#include "../View/View.h"

const unsigned int WINDOW_HEIGHT = 960;
const unsigned int WINDOW_WIDTH = 720;
const unsigned int TICK_PER_SEC = 60;
const double MS_PER_UPDATE = 1000. / TICK_PER_SEC;

class Game
{
private:
    unsigned int mapNumber;
    bool looping;
    Level *maps;
    SDL_Window *window;
    SDL_Surface *surface;
public:
    Game();
    ~Game();
    void init();
    void start();
    void shutdown();
private:
    void loop();
};

#endif //PROXIMACENTAURI_GAME_H