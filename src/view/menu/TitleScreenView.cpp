#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "TitleScreenView.h"
#include "../../ProximaCentauri.h"

TitleScreenView::TitleScreenView()
{
    initialized = false;
    mapSelection = nullptr;
    options = nullptr;
    quit = nullptr;
}

void TitleScreenView::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen view is already initialized.\n";
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

        SDL_Surface *mapSelectionSurface = TTF_RenderText_Blended(munro, "START GAME", SDL_Color {0, 0, 0, 255});
        SDL_Surface *optionsSurface = TTF_RenderText_Blended(munro, "OPTIONS", SDL_Color {0, 0, 0, 255});
        SDL_Surface *quitSurface = TTF_RenderText_Blended(munro, "QUIT", SDL_Color {0, 0, 0, 255});

        mapSelection = SDL_CreateTextureFromSurface(renderer, mapSelectionSurface);
        options = SDL_CreateTextureFromSurface(renderer, optionsSurface);
        quit = SDL_CreateTextureFromSurface(renderer, quitSurface);

        mapSelectionSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, mapSelectionSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), mapSelectionSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        mapSelectionDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSelectionSrcRect.w) / 2, static_cast<int_fast32_t>(5 * WINDOW_HEIGHT / 8) - mapSelectionSrcRect.h / 2, mapSelectionSrcRect.w, mapSelectionSrcRect.h};

        optionsSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, optionsSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), optionsSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        optionsDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - optionsSrcRect.w) / 2, static_cast<int_fast32_t>(3 * WINDOW_HEIGHT / 4) - optionsSrcRect.h / 2, optionsSrcRect.w, optionsSrcRect.h};

        quitSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, quitSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), quitSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        quitDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - quitSrcRect.w) / 2, static_cast<int_fast32_t>(7 * WINDOW_HEIGHT / 8) - quitSrcRect.h / 2, quitSrcRect.w, quitSrcRect.h};

        SDL_FreeSurface(mapSelectionSurface);
        SDL_FreeSurface(optionsSurface);
        SDL_FreeSurface(quitSurface);

        TTF_CloseFont(munro);

        initialized = true;
    }
}

TitleScreenView::~TitleScreenView()
{
    SDL_DestroyTexture(mapSelection);
    SDL_DestroyTexture(options);
    SDL_DestroyTexture(quit);
}

void TitleScreenView::render(uint_fast32_t selectedIndex) const
{
    if (initialized)
    {
        MenuView::render();

        SDL_Rect backgroundRect{MENU_SPACEING, WINDOW_HEIGHT / 2 + MENU_SPACEING, WINDOW_WIDTH - MENU_SPACEING * 2, WINDOW_HEIGHT / 2 - MENU_SPACEING * 2};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);

        SDL_RenderFillRect(renderer, &backgroundRect);

        SDL_RenderCopy(renderer, mapSelection, &mapSelectionSrcRect, &mapSelectionDstRect);
        SDL_RenderCopy(renderer, options, &optionsSrcRect, &optionsDstRect);
        SDL_RenderCopy(renderer, quit, &quitSrcRect, &quitDstRect);

        SDL_Rect underlineRect = {};
        switch (selectedIndex)
        {
            case 0:
                underlineRect = {mapSelectionDstRect.x, mapSelectionDstRect.y + mapSelectionDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), mapSelectionDstRect.w, UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {optionsDstRect.x, optionsDstRect.y + optionsDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), optionsDstRect.w, UNDERLINE_THICKNESS};
                break;
            case 2:
                underlineRect = {quitDstRect.x, quitDstRect.y + quitDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), quitDstRect.w, UNDERLINE_THICKNESS};
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
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void TitleScreenView::reset() const
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