#include <SDL2/SDL_ttf.h>
#include "OptionsView.h"

OptionsView::OptionsView()
{
    music = nullptr;
    sound = nullptr;
    layout = nullptr;
    back = nullptr;
    on = nullptr;
    off = nullptr;
    WASD = nullptr;
    ZQSD = nullptr;
    arrows = nullptr;
}

void OptionsView::init()
{
    MenuView::init();

    SDL_Color black = {0, 0, 0, 0};
    TTF_Font *munroMedium = TTF_OpenFont("resources/munro.ttf", 64);

    music = TTF_RenderUTF8_Blended(munroMedium, "MUSIC", black);
    sound = TTF_RenderUTF8_Blended(munroMedium, "SOUND", black);
    layout = TTF_RenderUTF8_Blended(munroMedium, "LAYOUT", black);
    back = TTF_RenderUTF8_Blended(munroMedium, "BACK", black);
    on = TTF_RenderUTF8_Blended(munroMedium, "ON", black);
    off = TTF_RenderUTF8_Blended(munroMedium, "OFF", black);
    WASD = TTF_RenderUTF8_Blended(munroMedium, "WASD", black);
    ZQSD = TTF_RenderUTF8_Blended(munroMedium, "ZQSD", black);
    arrows = TTF_RenderUTF8_Blended(munroMedium, "ARROWS", black);

    TTF_CloseFont(munroMedium);

    backgroundRect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    backRect = {(WINDOW_WIDTH - back->w) / 2 + 3, 9 * WINDOW_HEIGHT / 10 - back->h / 2 + 5, 0, 0};
}

OptionsView::~OptionsView()
{
    SDL_FreeSurface(music);
    SDL_FreeSurface(sound);
    SDL_FreeSurface(layout);
    SDL_FreeSurface(back);
    SDL_FreeSurface(on);
    SDL_FreeSurface(off);
    SDL_FreeSurface(WASD);
    SDL_FreeSurface(ZQSD);
    SDL_FreeSurface(arrows);
}

void OptionsView::preRender(bool music, bool sound, unsigned int selectedIndex, unsigned int selectedLayout)
{
    musicState = music;
    soundState = sound;
    this->selectedLayout = selectedLayout;

    musicRect = {(WINDOW_WIDTH - this->music->w - (music ? on : off)->w) / 2 - 16, 3 * WINDOW_HEIGHT / 5 - this->music->h / 2 + 5, 0, 0};
    soundRect = {(WINDOW_WIDTH - this->sound->w - (sound ? on : off)->w) / 2 - 16, 7 * WINDOW_HEIGHT / 10 - this->sound->h / 2 + 5, 0, 0};

    musicStateRect = {WINDOW_WIDTH / 2 + (this->music->w - (music ? on : off)->w) / 2 + 16, 3 * WINDOW_HEIGHT / 5 - this->music->h / 2 + 5, 0, 0};
    soundStateRect = {WINDOW_WIDTH / 2 + (this->sound->w - (sound ? on : off)->w) / 2 + 16, 7 * WINDOW_HEIGHT / 10 - this->sound->h / 2 + 5, 0, 0};

    WASDRect = {WINDOW_WIDTH / 2 + (this->layout->w - WASD->w) / 2 + 16, 4 * WINDOW_HEIGHT / 5 - this->layout->h / 2 + 5, 0, 0};
    ZQSDRect = {WINDOW_WIDTH / 2 + (this->layout->w - ZQSD->w) / 2 + 16, 4 * WINDOW_HEIGHT / 5 - this->layout->h / 2 + 5, 0, 0};
    arrowsSRect = {WINDOW_WIDTH / 2 + (this->layout->w - arrows->w) / 2 + 16, 4 * WINDOW_HEIGHT / 5 - this->layout->h / 2 + 5, 0, 0};

    switch (selectedLayout)
    {
        case 0:
            layoutRect = {(WINDOW_WIDTH - this->layout->w - WASD->w) / 2 - 16, 4 * WINDOW_HEIGHT / 5 - this->layout->h / 2 + 5, 0, 0};
            break;
        case 1:
            layoutRect = {(WINDOW_WIDTH - this->layout->w - ZQSD->w) / 2 - 16, 4 * WINDOW_HEIGHT / 5 - this->layout->h / 2 + 5, 0, 0};
            break;
        case 2:
            layoutRect = {(WINDOW_WIDTH - this->layout->w - arrows->w) / 2 - 16, 4 * WINDOW_HEIGHT / 5 - this->layout->h / 2 + 5, 0, 0};
            break;
        default:
            break;
    }

    switch (selectedIndex)
    {
        case 0:
            underlineRect = {musicRect.x, musicRect.y + this->music->h - 8, this->music->w + (music ? on : off)->w + 26, 6};
            break;
        case 1:
            underlineRect = {soundRect.x, soundRect.y + this->sound->h - 8, this->sound->w + (sound ? on : off)->w + 26, 6};
            break;
        case 2:
            switch (selectedLayout)
            {
                case 0:
                    underlineRect = {layoutRect.x, layoutRect.y + this->layout->h - 8, this->layout->w + WASD->w + 26, 6};
                    break;
                case 1:
                    underlineRect = {layoutRect.x, layoutRect.y + this->layout->h - 8, this->layout->w + ZQSD->w + 26, 6};
                    break;
                case 2:
                    underlineRect = {layoutRect.x, layoutRect.y + this->layout->h - 8, this->layout->w + arrows->w + 26, 6};
                    break;
                default:
                    break;
            }
            break;
        case 3:
            underlineRect = {backRect.x, backRect.y + this->back->h - 8, this->back->w - 6, 6};
            break;
        default:
            break;
    }
}

void OptionsView::reset()
{
    if (resetable)
    {
        MenuView::reset();
    }
    else
    {
        resetable = true;
    }
}

void OptionsView::render(SDL_Window *window)
{
    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x00FFFFFF);
    SDL_FillRect(SDL_GetWindowSurface(window), &underlineRect, 0x00000000);

    SDL_BlitSurface(music, nullptr, SDL_GetWindowSurface(window), &musicRect);
    SDL_BlitSurface(musicState ? on : off, nullptr, SDL_GetWindowSurface(window), &musicStateRect);
    SDL_BlitSurface(sound, nullptr, SDL_GetWindowSurface(window), &soundRect);
    SDL_BlitSurface(soundState ? on : off, nullptr, SDL_GetWindowSurface(window), &soundStateRect);
    SDL_BlitSurface(layout, nullptr, SDL_GetWindowSurface(window), &layoutRect);
    SDL_BlitSurface(back, nullptr, SDL_GetWindowSurface(window), &backRect);
    switch (selectedLayout)
    {
        case 0:
            SDL_BlitSurface(WASD, nullptr, SDL_GetWindowSurface(window), &WASDRect);
            break;
        case 1:
            SDL_BlitSurface(ZQSD, nullptr, SDL_GetWindowSurface(window), &ZQSDRect);
            break;
        case 2:
            SDL_BlitSurface(arrows, nullptr, SDL_GetWindowSurface(window), &arrowsSRect);
            break;
        default:
            break;
    }

    MenuView::render(window);
}