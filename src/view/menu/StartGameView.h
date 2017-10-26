#ifndef PROXIMACENTAURI_STARTGAMEVIEW_H
#define PROXIMACENTAURI_STARTGAMEVIEW_H

#include "MenuView.h"
#include "../../model/game/data/Level.h"

class StartGameView : public MenuView
{
private:
    uint_fast32_t mapNumber;
    uint_fast32_t startingMap;
    SDL_Rect backgroundRect;
    SDL_Rect underlineRect;
    SDL_Rect upRect;
    SDL_Rect downRect;
    SDL_Rect rects[4];
    SDL_Surface *up;
    SDL_Surface *down;
    SDL_Surface **maps;
    Level **mapsLevel;
public:
    StartGameView(uint_fast32_t mapNumber, Level **mapsLevel);
    void init() override;
    ~StartGameView() override;
    void reset() override;
    void preRender(uint_fast32_t selectedIndex);
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_STARTGAMEVIEW_H