#ifndef PROXIMACENTAURI_MENUVIEW_H
#define PROXIMACENTAURI_MENUVIEW_H

#include <SDL2/SDL_render.h>

class MenuView
{
protected:
    mutable int_fast32_t spriteIndex;
    SDL_Rect proximaSrcRect;
    SDL_Rect proximaDstRect;
    SDL_Rect centSrcRect;
    SDL_Rect centDstRect;
    SDL_Rect uriSrcRect;
    SDL_Rect uriDstRect;
    SDL_Rect spaceshipDstRect;
    SDL_Renderer *renderer;
    SDL_Texture *proxima;
    SDL_Texture *cent;
    SDL_Texture *uri;
protected:
    MenuView();
    virtual void init(SDL_Renderer *renderer);
    virtual ~MenuView();
    void render() const;
    virtual void reset() const;
};

#endif //PROXIMACENTAURI_MENUVIEW_H