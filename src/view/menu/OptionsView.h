#ifndef PROXIMACENTAURI_OPTIONSVIEW_H
#define PROXIMACENTAURI_OPTIONSVIEW_H

#include <SDL2/SDL_render.h>
#include "MenuView.h"
#include "../../model/menu/OptionsModel.h"

class OptionsView : private MenuView
{
private:
    bool initialized;
    SDL_Rect musicSrcRect;
    SDL_Rect soundSrcRect;
    SDL_Rect layoutSrcRect;
    SDL_Rect backSrcRect;
    SDL_Rect backDstRect;
    SDL_Rect onSrcRect;
    SDL_Rect offSrcRect;
    SDL_Rect WASDSrcRect;
    SDL_Rect ZQSDSrcRect;
    SDL_Rect ARROWSSrcRect;
    SDL_Texture *music;
    SDL_Texture *sound;
    SDL_Texture *layout;
    SDL_Texture *back;
    SDL_Texture *on;
    SDL_Texture *off;
    SDL_Texture *WASD;
    SDL_Texture *ZQSD;
    SDL_Texture *ARROWS;
public:
    OptionsView();
    void init(SDL_Renderer *renderer) override;
    ~OptionsView() override;
    void render(uint_fast32_t selectedIndex, bool music, bool sound, OptionsModel::KeyboardLayout layout) const;
    void reset() const override;
};

#endif //PROXIMACENTAURI_OPTIONSVIEW_H