#ifndef PROXIMACENTAURI_MODEL_H
#define PROXIMACENTAURI_MODEL_H

#include <SDL2/SDL_events.h>

class Model
{
public:
    virtual ~Model() = default;
    virtual void reset() = 0;
    virtual void update(SDL_Event *event) = 0;
};

#endif //PROXIMACENTAURI_MODEL_H
