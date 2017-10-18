#ifndef PROXIMACENTAURI_OPTIONSVIEW_H
#define PROXIMACENTAURI_OPTIONSVIEW_H

#include "MenuView.h"

class OptionsView : public MenuView
{
private:
    bool musicState;
    bool soundState;
    unsigned int selectedLayout;
    SDL_Rect backgroundRect;
    SDL_Rect musicRect;
    SDL_Rect musicStateRect;
    SDL_Rect soundRect;
    SDL_Rect soundStateRect;
    SDL_Rect layoutRect;
    SDL_Rect backRect;
    SDL_Rect underlineRect;
    SDL_Rect WASDRect;
    SDL_Rect ZQSDRect;
    SDL_Rect arrowsSRect;
    SDL_Surface *music;
    SDL_Surface *sound;
    SDL_Surface *layout;
    SDL_Surface *back;
    SDL_Surface *on;
    SDL_Surface *off;
    SDL_Surface *WASD;
    SDL_Surface *ZQSD;
    SDL_Surface *arrows;
public:
    OptionsView();
    void init() override;
    ~OptionsView() override;
    void preRender(bool music, bool sound, unsigned int selectedIndex, unsigned int selectedLayout);
    void render(SDL_Window *window) override;
};

#endif //PROXIMACENTAURI_OPTIONSVIEW_H