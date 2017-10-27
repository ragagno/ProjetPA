#ifndef PROXIMACENTAURI_ENTITYRENDERER_H
#define PROXIMACENTAURI_ENTITYRENDERER_H

#include <SDL2/SDL_video.h>
#include "../../../model/game/data/entity/Entity.h"

class EntityRenderer
{
public:
    void render(SDL_Window *window, Entity *entity) const;
};

#endif //PROXIMACENTAURI_ENTITYRENDERER_H
