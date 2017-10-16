#ifndef PROXIMACENTAURI_TITLESCREENVIEW_H
#define PROXIMACENTAURI_TITLESCREENVIEW_H

#include "MenuView.h"
#include "../../model/menu/TitleScreenModel.h"

class TitleScreenView : public MenuView
{
private:
    TitleScreenModel *model;
    SDL_Surface *startGame;
    SDL_Surface *options;
    SDL_Surface *quit;
public:
    explicit TitleScreenView(Model *model);
    ~TitleScreenView() override;
    void init() override;
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_TITLESCREENVIEW_H