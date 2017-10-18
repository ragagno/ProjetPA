#ifndef PROXIMACENTAURI_STARTGAMEVIEW_H
#define PROXIMACENTAURI_STARTGAMEVIEW_H

#include "MenuView.h"

class StartGameView : public MenuView
{
public:
    StartGameView() = default;
    void init() override;
    ~StartGameView() override = default;
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_STARTGAMEVIEW_H