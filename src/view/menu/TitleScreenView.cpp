#include <SDL2/SDL_ttf.h>
#include "TitleScreenView.h"

TitleScreenView::TitleScreenView()
{
    startGame = nullptr;
    options = nullptr;
    quit = nullptr;
}

void TitleScreenView::init()
{
    MenuView::init();

    SDL_Color black = {0, 0, 0, 0};

    TTF_Font *munroMedium = TTF_OpenFont("resources/munro.ttf", 64);

    startGame = TTF_RenderUTF8_Blended(munroMedium, "START GAME", black);
    options = TTF_RenderUTF8_Blended(munroMedium, "OPTIONS", black);
    quit = TTF_RenderUTF8_Blended(munroMedium, "QUIT", black);

    TTF_CloseFont(munroMedium);

    backgroundRect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    startGameRect = {(WINDOW_WIDTH - startGame->w) / 2 + 3, 5 * WINDOW_HEIGHT / 8 - startGame->h / 2 + 5, 0, 0};
    optionsRect = {(WINDOW_WIDTH - options->w) / 2 + 3, 3 * WINDOW_HEIGHT / 4 - options->h / 2 + 5, 0, 0};
    quitRect = {(WINDOW_WIDTH - quit->w) / 2 + 3, 7 * WINDOW_HEIGHT / 8 - quit->h / 2 + 5, 0, 0};
}

TitleScreenView::~TitleScreenView()
{
    SDL_free(startGame);
    SDL_free(options);
    SDL_free(quit);
}

void TitleScreenView::preRender(unsigned int selectedIndex)
{
    switch (selectedIndex)
    {
        case 0:
            underlineRect = {startGameRect.x, startGameRect.y + startGameRect.h - 8, startGameRect.w - 6, 6};
            break;
        case 1:
            underlineRect = {optionsRect.x, optionsRect.y + optionsRect.h - 8, optionsRect.w - 6, 6};
            break;
        case 2:
            underlineRect = {quitRect.x, quitRect.y + quitRect.h - 8, quitRect.w - 6, 6};
            break;
        default:
            break;
    }
}

void TitleScreenView::render(SDL_Window *window)
{
    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x00FFFFFF);
    SDL_FillRect(SDL_GetWindowSurface(window), &underlineRect, 0x00000000);

    SDL_BlitSurface(startGame, nullptr, SDL_GetWindowSurface(window), &startGameRect);
    SDL_BlitSurface(options, nullptr, SDL_GetWindowSurface(window), &optionsRect);
    SDL_BlitSurface(quit, nullptr, SDL_GetWindowSurface(window), &quitRect);

    MenuView::render(window);
}