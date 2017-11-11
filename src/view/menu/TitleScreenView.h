#ifndef PROXIMACENTAURI_TITLESCREENVIEW_H
#define PROXIMACENTAURI_TITLESCREENVIEW_H

#include <SDL2/SDL_render.h>
#include "MenuView.h"

class TitleScreenView : private MenuView
{
private:
    bool initialized;
    SDL_Rect mapSelectionSrcRect;
    SDL_Rect mapSelectionDstRect;
    SDL_Rect optionsSrcRect;
    SDL_Rect optionsDstRect;
    SDL_Rect quitSrcRect;
    SDL_Rect quitDstRect;
    SDL_Texture *mapSelection;
    SDL_Texture *options;
    SDL_Texture *quit;
public:
    TitleScreenView();
    void init(SDL_Renderer *renderer) override;
    ~TitleScreenView() override;
    void render(uint_fast32_t selectedIndex) const;
    void reset() const override;
};

#endif //PROXIMACENTAURI_TITLESCREENVIEW_H