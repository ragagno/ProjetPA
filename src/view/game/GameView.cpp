#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "GameView.h"
#include "../../ProximaCentauri.h"

GameView::GameView()
{
    initialized = false;
}

void GameView::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is already initialized.\n";
    }
    else
    {
        this->renderer = renderer;

        TTF_Font *munro = TTF_OpenFont("resources/munro.ttf", 64);
        if (munro == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Resource munro.ttf could not be loaded.\n";
            exit(EXIT_FAILURE);
        }

        SDL_Surface *resumeSurface = TTF_RenderText_Blended(munro, "RESUME", SDL_Color {0, 0, 0, 255});
        SDL_Surface *quitSurface = TTF_RenderText_Blended(munro, "QUIT", SDL_Color {0, 0, 0, 255});

        resume = SDL_CreateTextureFromSurface(renderer, resumeSurface);
        quit = SDL_CreateTextureFromSurface(renderer, quitSurface);

        resumeSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, resumeSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), resumeSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        quitSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, quitSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), quitSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        SDL_FreeSurface(resumeSurface);
        SDL_FreeSurface(quitSurface);

        TTF_CloseFont(munro);

        initialized = true;
    }
}

GameView::~GameView()
{

}

void GameView::render(Player player) const
{
    if (initialized)
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

        SDL_Rect playerSrcRect{0, 0, SPACESHIP_WIDTH, SPACESHIP_HEIGHT};
        SDL_Rect playerDstRect{player.getX(), player.getY(), SPACESHIP_WIDTH, SPACESHIP_HEIGHT};
        SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getSpaceshipSprite(), &playerSrcRect, &playerDstRect);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameView::renderPause(uint_fast32_t selectedIndex) const
{
    if (initialized)
    {
        SDL_Rect resumeDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - resumeSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT - 3 * resumeSrcRect.h) / 2, resumeSrcRect.w, resumeSrcRect.h};
        SDL_Rect quitDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - quitSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT + quitSrcRect.h) / 2, quitSrcRect.w, quitSrcRect.h};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
        SDL_Rect menuBackgroundRect{resumeDstRect.x - static_cast<int_fast32_t>(MENU_SPACEING), resumeDstRect.y - static_cast<int_fast32_t>(MENU_SPACEING), resumeDstRect.w + 2 * static_cast<int_fast32_t>(MENU_SPACEING), 2 * static_cast<int_fast32_t>(MENU_SPACEING) + (3 * resumeDstRect.h + 3 * quitDstRect.h) / 2};
        SDL_RenderFillRect(renderer, &menuBackgroundRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect underlineRect{};

        switch (selectedIndex)
        {
            case 0:
                underlineRect = {resumeDstRect.x, resumeDstRect.y + resumeDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), resumeDstRect.w, UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {quitDstRect.x, quitDstRect.y + quitDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), quitDstRect.w, UNDERLINE_THICKNESS};
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << selectedIndex << "\n";
                exit(EXIT_FAILURE);
        }

        SDL_RenderFillRect(renderer, &underlineRect);

        SDL_RenderCopy(renderer, resume, &resumeSrcRect, &resumeDstRect);
        SDL_RenderCopy(renderer, quit, &quitSrcRect, &quitDstRect);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameView::reset() const
{
    if (initialized)
    {

    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}