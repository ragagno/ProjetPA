#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "MenuView.h"

MenuView::MenuView()
{
    proxima = nullptr;
    cent = nullptr;
    spaceship = nullptr;
    uri = nullptr;
    version = nullptr;
    author = nullptr;
}

void MenuView::init()
{
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255, 255, 0};

    TTF_Font *munroBig = TTF_OpenFont("resources/munro.ttf", 144);
    TTF_Font *munroSmall = TTF_OpenFont("resources/munro.ttf", 32);

    proxima = TTF_RenderUTF8_Blended(munroBig, "PROXIMA", white);
    cent = TTF_RenderUTF8_Blended(munroBig, "CENT", white);
    uri = TTF_RenderUTF8_Blended(munroBig, "URI", white);
    version = TTF_RenderUTF8_Blended(munroSmall, VERSION, black);
    author = TTF_RenderUTF8_Blended(munroSmall, AUTHOR, black);

    spaceship = IMG_Load("resources/spaceship.png");

    TTF_CloseFont(munroBig);
    TTF_CloseFont(munroSmall);
}

void MenuView::render(SDL_Window *window)
{
    static SDL_Rect backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    static SDL_Rect proximaRect = {WINDOW_WIDTH / 2 - proxima->w / 2 + 7, WINDOW_HEIGHT / 4 - proxima->h + 24, 0, 0};
    static SDL_Rect centRect = {WINDOW_WIDTH / 2 - proxima->w / 2 + 7, WINDOW_HEIGHT / 4, 0, 0};
    static SDL_Rect spaceshipRect = {WINDOW_WIDTH / 2 - proxima->w / 2 + 7 + cent->w, WINDOW_HEIGHT / 4 + 7, 0, 0};
    static SDL_Rect uriRect = {WINDOW_WIDTH / 2 + proxima->w / 2 - uri->w + 7, WINDOW_HEIGHT / 4, 0, 0};
    static SDL_Rect versionRect = {8, WINDOW_HEIGHT - 32, 0, 0};
    static SDL_Rect authorRect = {WINDOW_WIDTH - author->w - 5, WINDOW_HEIGHT - 32, 0, 0};

    static int spaceshipFrame = 0;
    SDL_Rect spaceshipFrameRect = {(spaceship->w / 4) * ((spaceshipFrame++ * 2 % 40) / 10), 0, spaceship->w / 4, spaceship->h};

    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x00000000);

    SDL_BlitSurface(proxima, nullptr, SDL_GetWindowSurface(window), &proximaRect);
    SDL_BlitSurface(cent, nullptr, SDL_GetWindowSurface(window), &centRect);
    SDL_BlitSurface(spaceship, &spaceshipFrameRect, SDL_GetWindowSurface(window), &spaceshipRect);
    SDL_BlitSurface(uri, nullptr, SDL_GetWindowSurface(window), &uriRect);
    SDL_BlitSurface(version, nullptr, SDL_GetWindowSurface(window), &versionRect);
    SDL_BlitSurface(author, nullptr, SDL_GetWindowSurface(window), &authorRect);
}

MenuView::~MenuView()
{
    SDL_FreeSurface(proxima);
    SDL_FreeSurface(cent);
    SDL_FreeSurface(spaceship);
    SDL_FreeSurface(uri);
    SDL_FreeSurface(version);
    SDL_FreeSurface(author);
}