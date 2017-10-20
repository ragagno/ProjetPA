#ifndef PROXIMACENTAURI_STARTGAMEVIEW_H
#define PROXIMACENTAURI_STARTGAMEVIEW_H

#include "MenuView.h"
#include "../../model/Level.h"

class StartGameView : public MenuView
{
private:
    unsigned int mapNumber;
    unsigned int startingMap;
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
    StartGameView(unsigned int mapNumber, Level **mapsLevel);
    void init() override;
    ~StartGameView() override;
    void preRender(unsigned int selectedIndex);
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_STARTGAMEVIEW_H