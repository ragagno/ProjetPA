#ifndef PROXIMACENTAURI_TITLESCREENVIEW_H
#define PROXIMACENTAURI_TITLESCREENVIEW_H

#include "MenuView.h"

class TitleScreenView : public MenuView
{
private:
    SDL_Rect backgroundRect;
    SDL_Rect startGameRect;
    SDL_Rect optionsRect;
    SDL_Rect quitRect;
    SDL_Rect underlineRect;
    SDL_Surface *startGame;
    SDL_Surface *options;
    SDL_Surface *quit;
public:
    TitleScreenView();
    ~TitleScreenView() override;
    void init() override;
    void render(SDL_Window *window) override;
    void preRender(unsigned int selectedIndex);
};

#endif //PROXIMACENTAURI_TITLESCREENVIEW_H