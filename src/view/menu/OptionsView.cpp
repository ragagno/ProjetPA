#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "OptionsView.h"
#include "../../ProximaCentauri.h"

OptionsView::OptionsView()
{
    initialized = false;
    music = nullptr;
    sound = nullptr;
    layout = nullptr;
    back = nullptr;
    on = nullptr;
    off = nullptr;
    WASD = nullptr;
    ZQSD = nullptr;
    ARROWS = nullptr;
    renderer = nullptr;
}

void OptionsView::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options view is already initialized.\n";
    }
    else
    {
        MenuView::init(renderer);

        TTF_Font *munro = TTF_OpenFont("resources/munro.ttf", 64);
        if (munro == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Resource munro.ttf could not be loaded.\n";
            exit(EXIT_FAILURE);
        }

        SDL_Surface *musicSurface = TTF_RenderText_Blended(munro, "MUSIC", SDL_Color {0, 0, 0, 255});
        SDL_Surface *soundSurface = TTF_RenderText_Blended(munro, "SOUND", SDL_Color {0, 0, 0, 255});
        SDL_Surface *layoutSurface = TTF_RenderText_Blended(munro, "LAYOUT", SDL_Color {0, 0, 0, 255});
        SDL_Surface *backSurface = TTF_RenderText_Blended(munro, "BACK", SDL_Color {0, 0, 0, 255});
        SDL_Surface *onSurface = TTF_RenderText_Blended(munro, "ON", SDL_Color {0, 0, 0, 255});
        SDL_Surface *offSurface = TTF_RenderText_Blended(munro, "OFF", SDL_Color {0, 0, 0, 255});
        SDL_Surface *WASDSurface = TTF_RenderText_Blended(munro, "WASD", SDL_Color {0, 0, 0, 255});
        SDL_Surface *ZQSDSurface = TTF_RenderText_Blended(munro, "ZQSD", SDL_Color {0, 0, 0, 255});
        SDL_Surface *ARROWSSurface = TTF_RenderText_Blended(munro, "ARROWS", SDL_Color {0, 0, 0, 255});

        music = SDL_CreateTextureFromSurface(renderer, musicSurface);
        sound = SDL_CreateTextureFromSurface(renderer, soundSurface);
        layout = SDL_CreateTextureFromSurface(renderer, layoutSurface);
        back = SDL_CreateTextureFromSurface(renderer, backSurface);
        on = SDL_CreateTextureFromSurface(renderer, onSurface);
        off = SDL_CreateTextureFromSurface(renderer, offSurface);
        WASD = SDL_CreateTextureFromSurface(renderer, WASDSurface);
        ZQSD = SDL_CreateTextureFromSurface(renderer, ZQSDSurface);
        ARROWS = SDL_CreateTextureFromSurface(renderer, ARROWSSurface);

        musicSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, musicSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), musicSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        soundSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, soundSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), soundSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        layoutSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, layoutSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), layoutSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        backSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, backSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), backSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        backDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - backSrcRect.w) / 2, static_cast<int_fast32_t>(9 * WINDOW_HEIGHT / 10) - backSrcRect.h / 2, backSrcRect.w, backSrcRect.h};

        onSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, onSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), onSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        offSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, offSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), offSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        WASDSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, WASDSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), WASDSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        ZQSDSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, ZQSDSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), ZQSDSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        ARROWSSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, ARROWSSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), ARROWSSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        SDL_FreeSurface(musicSurface);
        SDL_FreeSurface(soundSurface);
        SDL_FreeSurface(layoutSurface);
        SDL_FreeSurface(backSurface);
        SDL_FreeSurface(onSurface);
        SDL_FreeSurface(offSurface);
        SDL_FreeSurface(WASDSurface);
        SDL_FreeSurface(ZQSDSurface);
        SDL_FreeSurface(ARROWSSurface);

        TTF_CloseFont(munro);

        initialized = true;
    }
}

OptionsView::~OptionsView()
{
    SDL_DestroyTexture(music);
    SDL_DestroyTexture(sound);
    SDL_DestroyTexture(layout);
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(on);
    SDL_DestroyTexture(off);
    SDL_DestroyTexture(WASD);
    SDL_DestroyTexture(ZQSD);
    SDL_DestroyTexture(ARROWS);
}

void OptionsView::render(uint_fast32_t selectedIndex, bool musicState, bool soundState, OptionsModel::KeyboardLayout currentLayout) const
{
    if (initialized)
    {
        MenuView::render();

        SDL_Rect backgroundRect{MENU_SPACEING, WINDOW_HEIGHT / 2 + MENU_SPACEING, WINDOW_WIDTH - MENU_SPACEING * 2, WINDOW_HEIGHT / 2 - MENU_SPACEING * 2};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);

        SDL_RenderFillRect(renderer, &backgroundRect);

        SDL_Rect musicDstRect{0, static_cast<int_fast32_t>(6 * WINDOW_HEIGHT / 10) - musicSrcRect.h / 2, musicSrcRect.w, musicSrcRect.h};
        SDL_Rect musicStateDstRect{0, musicDstRect.y, 0, musicSrcRect.h};
        if (musicState)
        {
            musicDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (musicSrcRect.w + onSrcRect.w)) / 2;
            musicStateDstRect.x = musicDstRect.x + musicDstRect.w + SPACE_WIDTH;
            musicStateDstRect.w = onSrcRect.w;
            SDL_RenderCopy(renderer, on, &onSrcRect, &musicStateDstRect);
        }
        else
        {
            musicDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (musicSrcRect.w + offSrcRect.w)) / 2;
            musicStateDstRect.x = musicDstRect.x + musicDstRect.w + SPACE_WIDTH;
            musicStateDstRect.w = offSrcRect.w;
            SDL_RenderCopy(renderer, off, &offSrcRect, &musicStateDstRect);
        }
        SDL_RenderCopy(renderer, music, &musicSrcRect, &musicDstRect);

        SDL_Rect soundDstRect{0, static_cast<int_fast32_t>(7 * WINDOW_HEIGHT / 10) - soundSrcRect.h / 2, soundSrcRect.w, soundSrcRect.h};;
        SDL_Rect soundStateDstRect{0, soundDstRect.y, 0, soundSrcRect.h};
        if (soundState)
        {
            soundDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (soundSrcRect.w + onSrcRect.w)) / 2;
            soundStateDstRect.x = soundDstRect.x + soundDstRect.w + SPACE_WIDTH;
            soundStateDstRect.w = onSrcRect.w;
            SDL_RenderCopy(renderer, on, &onSrcRect, &soundStateDstRect);
        }
        else
        {
            soundDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (soundSrcRect.w + offSrcRect.w)) / 2;
            soundStateDstRect.x = soundDstRect.x + soundDstRect.w + SPACE_WIDTH;
            soundStateDstRect.w = offSrcRect.w;
            SDL_RenderCopy(renderer, off, &offSrcRect, &soundStateDstRect);
        }
        SDL_RenderCopy(renderer, sound, &soundSrcRect, &soundDstRect);

        SDL_Rect layoutDstRect{0, static_cast<int_fast32_t>(8 * WINDOW_HEIGHT / 10) - layoutSrcRect.h / 2, layoutSrcRect.w, layoutSrcRect.h};;
        SDL_Rect layoutStateDstRect{0, layoutDstRect.y, 0, layoutSrcRect.h};
        switch (currentLayout)
        {
            case OptionsModel::WASD:
                layoutDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (layoutSrcRect.w + WASDSrcRect.w)) / 2;
                layoutStateDstRect.x = layoutDstRect.x + layoutDstRect.w + SPACE_WIDTH;
                layoutStateDstRect.w = WASDSrcRect.w;
                SDL_RenderCopy(renderer, WASD, &WASDSrcRect, &layoutStateDstRect);
                break;
            case OptionsModel::ZQSD:
                layoutDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (layoutSrcRect.w + ZQSDSrcRect.w)) / 2;
                layoutStateDstRect.x = layoutDstRect.x + layoutDstRect.w + SPACE_WIDTH;
                layoutStateDstRect.w = ZQSDSrcRect.w;
                SDL_RenderCopy(renderer, ZQSD, &ZQSDSrcRect, &layoutStateDstRect);
                break;
            case OptionsModel::ARROWS:
                layoutDstRect.x = static_cast<int_fast32_t>(WINDOW_WIDTH - (layoutSrcRect.w + ARROWSSrcRect.w)) / 2;
                layoutStateDstRect.x = layoutDstRect.x + layoutDstRect.w + SPACE_WIDTH;
                layoutStateDstRect.w = ARROWSSrcRect.w;
                SDL_RenderCopy(renderer, ARROWS, &ARROWSSrcRect, &layoutStateDstRect);
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected layout: " << currentLayout << "\n";
                exit(EXIT_FAILURE);
        }
        SDL_RenderCopy(renderer, layout, &layoutSrcRect, &layoutDstRect);

        SDL_RenderCopy(renderer, back, &backSrcRect, &backDstRect);

        SDL_Rect underlineRect = {};
        switch (selectedIndex)
        {
            case 0:
                underlineRect = {musicDstRect.x, musicDstRect.y + musicDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), musicDstRect.w + static_cast<int_fast32_t>(SPACE_WIDTH) + (musicState ? onSrcRect.w : offSrcRect.w), UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {soundDstRect.x, soundDstRect.y + soundDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), soundDstRect.w + static_cast<int_fast32_t>(SPACE_WIDTH) + (soundState ? onSrcRect.w : offSrcRect.w), UNDERLINE_THICKNESS};
                break;
            case 2:
                switch (currentLayout)
                {
                    case OptionsModel::WASD:
                        underlineRect = {layoutDstRect.x, layoutDstRect.y + layoutDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), layoutDstRect.w + static_cast<int_fast32_t>(SPACE_WIDTH) + WASDSrcRect.w, UNDERLINE_THICKNESS};
                        break;
                    case OptionsModel::ZQSD:
                        underlineRect = {layoutDstRect.x, layoutDstRect.y + layoutDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), layoutDstRect.w + static_cast<int_fast32_t>(SPACE_WIDTH) + ZQSDSrcRect.w, UNDERLINE_THICKNESS};
                        break;
                    case OptionsModel::ARROWS:
                        underlineRect = {layoutDstRect.x, layoutDstRect.y + layoutDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), layoutDstRect.w + static_cast<int_fast32_t>(SPACE_WIDTH) + ARROWSSrcRect.w, UNDERLINE_THICKNESS};
                        break;
                    default:
                        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected layout: " << layout << "\n";
                        exit(EXIT_FAILURE);
                }
                break;
            case 3:
                underlineRect = {backDstRect.x, backDstRect.y + backDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), backDstRect.w, UNDERLINE_THICKNESS};
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << selectedIndex << "\n";
                exit(EXIT_FAILURE);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &underlineRect);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsView::reset() const
{
    if (initialized)
    {
        MenuView::reset();
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}