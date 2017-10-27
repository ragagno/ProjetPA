#include "EntityRenderer.h"
#include "../../View.h"

void EntityRenderer::render(SDL_Window *window, Entity *entity) const
{
    SDL_Rect rect = {static_cast<int_fast32_t>(entity->getX()), static_cast<int_fast32_t>(WINDOW_HEIGHT - entity->getY()) + 98, 56, 98};
    SDL_FillRect(SDL_GetWindowSurface(window), &rect, 0x007F7F7F);
}
