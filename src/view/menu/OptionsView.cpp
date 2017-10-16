#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "OptionsView.h"

void OptionsView::init()
{
    MenuView::init();

    SDL_Color black = {0, 0, 0, 0};

    TTF_Font *munroMedium = TTF_OpenFont("resources/munro.ttf", 64);

    music = TTF_RenderUTF8_Blended(munroMedium, "MUSIC", black);
    sound = TTF_RenderUTF8_Blended(munroMedium, "SOUND", black);
    controls = TTF_RenderUTF8_Blended(munroMedium, "CONTROLS", black);
    back = TTF_RenderUTF8_Blended(munroMedium, "BACK", black);
    on = TTF_RenderUTF8_Blended(munroMedium, "ON", black);
    off = TTF_RenderUTF8_Blended(munroMedium, "OFF", black);

    TTF_CloseFont(munroMedium);

    backgroundRect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    controlsRect = {(WINDOW_WIDTH - controls->w) / 2 + 3, 4 * WINDOW_HEIGHT / 5 - controls->h / 2 + 5, 0, 0};
    backRect = {(WINDOW_WIDTH - back->w) / 2 + 3, 9 * WINDOW_HEIGHT / 10 - back->h / 2 + 5, 0, 0};
}

void OptionsView::render(SDL_Window *window)
{
    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x00FFFFFF);
    SDL_FillRect(SDL_GetWindowSurface(window), &underlineRect, 0x00000000);

    SDL_BlitSurface(music, nullptr, SDL_GetWindowSurface(window), &musicRect);
    SDL_BlitSurface(musicState ? on : off, nullptr, SDL_GetWindowSurface(window), &musicStateRect);
    SDL_BlitSurface(sound, nullptr, SDL_GetWindowSurface(window), &soundRect);
    SDL_BlitSurface(soundState ? on : off, nullptr, SDL_GetWindowSurface(window), &soundStateRect);
    SDL_BlitSurface(controls, nullptr, SDL_GetWindowSurface(window), &controlsRect);
    SDL_BlitSurface(back, nullptr, SDL_GetWindowSurface(window), &backRect);

    MenuView::render(window);
}

OptionsView::OptionsView()
{
    music = nullptr;
    sound = nullptr;
    controls = nullptr;
    back = nullptr;
    on = nullptr;
    off = nullptr;
}

OptionsView::~OptionsView()
{
    SDL_FreeSurface(music);
    SDL_FreeSurface(sound);
    SDL_FreeSurface(controls);
    SDL_FreeSurface(back);
    SDL_FreeSurface(on);
    SDL_FreeSurface(off);
}

void OptionsView::preRender(bool music, bool sound, unsigned int selectedIndex)
{
    musicState = music;
    soundState = sound;
    musicRect = {(WINDOW_WIDTH - this->music->w - (music ? on : off)->w) / 2 - 16, 3 * WINDOW_HEIGHT / 5 - this->music->h / 2 + 5, 0, 0};
    soundRect = {(WINDOW_WIDTH - this->sound->w - (sound ? on : off)->w) / 2 - 16, 7 * WINDOW_HEIGHT / 10 - this->sound->h / 2 + 5, 0, 0};
    musicStateRect = {WINDOW_WIDTH / 2 + (this->music->w - (music ? on : off)->w) / 2 + 16, 3 * WINDOW_HEIGHT / 5 - this->music->h / 2 + 5, 0, 0};
    soundStateRect = {WINDOW_WIDTH / 2 + (this->sound->w - (sound ? on : off)->w) / 2 + 16, 7 * WINDOW_HEIGHT / 10 - this->sound->h / 2 + 5, 0, 0};
    switch (selectedIndex)
    {
        case 0:
            underlineRect = {musicRect.x, musicRect.y + this->music->h - 8, this->music->w + (music ? on : off)->w + 26, 6};
            break;
        case 1:
            underlineRect = {soundRect.x, soundRect.y + this->sound->h - 8, this->sound->w + (sound ? on : off)->w + 26, 6};
            break;
        case 2:
            underlineRect = {controlsRect.x, controlsRect.y + this->controls->h - 8, this->controls->w - 6, 6};
            break;
        case 3:
            underlineRect = {backRect.x, backRect.y + this->back->h - 8, this->back->w - 6, 6};
            break;
        default:
            break;
    }
}
