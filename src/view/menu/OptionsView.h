#ifndef PROXIMACENTAURI_OPTIONSVIEW_H
#define PROXIMACENTAURI_OPTIONSVIEW_H

#include "MenuView.h"

class OptionsView : public MenuView
{
private:
    bool musicState;
    bool soundState;
    SDL_Rect backgroundRect;
    SDL_Rect musicRect;
    SDL_Rect musicStateRect;
    SDL_Rect soundRect;
    SDL_Rect soundStateRect;
    SDL_Rect controlsRect;
    SDL_Rect backRect;
    SDL_Rect underlineRect;
    SDL_Surface *music;
    SDL_Surface *sound;
    SDL_Surface *controls;
    SDL_Surface *back;
    SDL_Surface *on;
    SDL_Surface *off;
public:
    OptionsView();
    ~OptionsView() override;
    void preRender(bool music, bool sound, unsigned int selectedIndex);
    void init() override;
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_OPTIONSVIEW_H