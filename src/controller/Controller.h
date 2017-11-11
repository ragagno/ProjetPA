#ifndef PROXIMACENTAURI_CONTROLLER_H
#define PROXIMACENTAURI_CONTROLLER_H

#include <SDL2/SDL_render.h>

class Controller
{
public:
    Controller() = default;
    virtual void init(SDL_Renderer *renderer) = 0;
    virtual ~Controller() = default;
    virtual void tick(long double ticks) = 0;
    virtual void render() = 0;
};

#endif //PROXIMACENTAURI_CONTROLLER_H