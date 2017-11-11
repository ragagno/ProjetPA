#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "MenuView.h"
#include "../../ProximaCentauri.h"

MenuView::MenuView()
{
    renderer = nullptr;
    proxima = nullptr;
    cent = nullptr;
    uri = nullptr;
}

void MenuView::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    spriteIndex = 0;

    TTF_Font *munro = TTF_OpenFont("resources/munro.ttf", 144);
    if (munro == nullptr)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Resource munro.ttf could not be loaded.\n";
        exit(EXIT_FAILURE);
    }

    SDL_Surface *proximaSurface = TTF_RenderText_Blended(munro, "PROXIMA", SDL_Color {255, 255, 255, 255});
    SDL_Surface *centSurface = TTF_RenderText_Blended(munro, "CENT", SDL_Color {255, 255, 255, 255});
    SDL_Surface *uriSurface = TTF_RenderText_Blended(munro, "URI", SDL_Color {255, 255, 255, 255});

    proxima = SDL_CreateTextureFromSurface(renderer, proximaSurface);
    cent = SDL_CreateTextureFromSurface(renderer, centSurface);
    uri = SDL_CreateTextureFromSurface(renderer, uriSurface);

    proximaSrcRect = {SDL_ttfDumbLeftMargin_144, SDL_ttfDumbTopMargin_144, proximaSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_144 + SDL_ttfDumbLeftMargin_144), proximaSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_144 + SDL_ttfDumbBottomMargin_144)};
    proximaDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - proximaSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT / 4) - (5 * proximaSrcRect.h / 4), proximaSrcRect.w, proximaSrcRect.h};

    centSrcRect = {SDL_ttfDumbLeftMargin_144, SDL_ttfDumbTopMargin_144, centSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_144 + SDL_ttfDumbLeftMargin_144), centSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_144 + SDL_ttfDumbBottomMargin_144)};
    centDstRect = {proximaDstRect.x, static_cast<int_fast32_t>(WINDOW_HEIGHT / 4) + (centSrcRect.h / 4), centSrcRect.w, centSrcRect.h};

    uriSrcRect = {SDL_ttfDumbLeftMargin_144, SDL_ttfDumbTopMargin_144, uriSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_144 + SDL_ttfDumbLeftMargin_144), uriSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_144 + SDL_ttfDumbBottomMargin_144)};
    uriDstRect = {(proximaDstRect.x + proximaDstRect.w) - uriSrcRect.w, static_cast<int_fast32_t>(WINDOW_HEIGHT / 4) + (uriSrcRect.h / 4), uriSrcRect.w, uriSrcRect.h};

    int_fast32_t w;
    int_fast32_t h;

    SDL_QueryTexture(ProximaCentauri::getInstance()->getSpaceshipSprite(), nullptr, nullptr, &w, &h);

    spaceshipDstRect = {(centDstRect.x + centDstRect.w) + (uriDstRect.x - (centDstRect.x + centDstRect.w + (w / 4))) / 2, uriDstRect.y, w / 4, h};

    SDL_FreeSurface(proximaSurface);
    SDL_FreeSurface(centSurface);
    SDL_FreeSurface(uriSurface);

    TTF_CloseFont(munro);
}

MenuView::~MenuView()
{
    SDL_DestroyTexture(proxima);
    SDL_DestroyTexture(cent);
    SDL_DestroyTexture(uri);
}

void MenuView::render() const
{
    if (ProximaCentauri::getInstance()->getBackgroundOffset() < WINDOW_HEIGHT)
    {
        SDL_Rect backgroundSrcRect{0, static_cast<int_fast32_t>((WINDOW_HEIGHT - 1) - ProximaCentauri::getInstance()->getBackgroundOffset()), WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_Rect backgroundDstRect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getStarBackground(), &backgroundSrcRect, &backgroundDstRect);
    }
    else
    {
        SDL_Rect backgroundSrcRect1{0, 0, WINDOW_WIDTH, static_cast<int_fast32_t>(WINDOW_HEIGHT * 2 - ProximaCentauri::getInstance()->getBackgroundOffset())};
        SDL_Rect backgroundDstRect1{0, static_cast<int_fast32_t>(ProximaCentauri::getInstance()->getBackgroundOffset() - WINDOW_HEIGHT), WINDOW_WIDTH, backgroundSrcRect1.h};
        SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getStarBackground(), &backgroundSrcRect1, &backgroundDstRect1);

        SDL_Rect backgroundSrcRect2{0, static_cast<int_fast32_t>(WINDOW_HEIGHT) + backgroundSrcRect1.h, WINDOW_WIDTH, static_cast<int_fast32_t>(WINDOW_HEIGHT) - backgroundSrcRect1.h};
        SDL_Rect backgroundDstRect2{0, 0, WINDOW_WIDTH, backgroundSrcRect2.h};
        SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getStarBackground(), &backgroundSrcRect2, &backgroundDstRect2);
    }

    SDL_RenderCopy(renderer, proxima, &proximaSrcRect, &proximaDstRect);
    SDL_RenderCopy(renderer, cent, &centSrcRect, &centDstRect);
    SDL_RenderCopy(renderer, uri, &uriSrcRect, &uriDstRect);

    SDL_Rect spaceshipSrcRect{static_cast<int_fast32_t>(spriteIndex / TICK_PER_SPRITE_SPACESHIP) * spaceshipDstRect.w, 0, spaceshipDstRect.w, spaceshipDstRect.h};
    SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getSpaceshipSprite(), &spaceshipSrcRect, &spaceshipDstRect);

    if (++spriteIndex == 3 * TICK_PER_SPRITE_SPACESHIP)
    {
        spriteIndex = 0;
    }
}

void MenuView::reset() const
{
    spriteIndex = 0;
}