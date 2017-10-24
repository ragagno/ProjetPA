#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "StartGameView.h"

StartGameView::StartGameView(unsigned int mapNumber, Level **mapsLevel)
{
    up = nullptr;
    down = nullptr;
    maps = new SDL_Surface *[mapNumber];
    for (unsigned int i = 0; i < mapNumber; i++)
    {
        maps[i] = nullptr;
    }
    rects[0] = {};
    rects[1] = {};
    rects[2] = {};
    rects[3] = {};
    this->mapsLevel = mapsLevel;
    this->mapNumber = mapNumber;
    startingMap = 0;
}

void StartGameView::init()
{
    MenuView::init();

    up = IMG_Load("resources/up.png");
    down = IMG_Load("resources/down.png");

    SDL_Color black = {0, 0, 0, 0};
    TTF_Font *munroMedium = TTF_OpenFont("resources/munro.ttf", 64);

    for (unsigned int i = 0; i < mapNumber; ++i)
    {
        maps[i] = TTF_RenderUTF8_Blended(munroMedium, (*mapsLevel)[i].getName().c_str(), black);
        int j = 0;
        while (maps[i]->w > 620)
        {
            SDL_FreeSurface(maps[i]);
            maps[i] = TTF_RenderUTF8_Blended(munroMedium, ((*mapsLevel)[i].getName().substr(0, (*mapsLevel)[i].getName().length() - j++) + "...").c_str(), black);
        }
    }

    TTF_CloseFont(munroMedium);

    backgroundRect = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    upRect = {(WINDOW_WIDTH - up->w)/ 2, 13 * WINDOW_HEIGHT / 24 - up->h / 2, 0, 0};
    downRect = {(WINDOW_WIDTH - down->w)/ 2, 23 * WINDOW_HEIGHT / 24 - down->h / 2, 0, 0};

    switch (mapNumber)
    {
        case 1:
            rects[0] = {(WINDOW_WIDTH - maps[0]->w) / 2 + 3, 3 * WINDOW_HEIGHT / 4 - maps[0]->h / 2 + 5, 0, 0};
            break;
        case 2:
            rects[0] = {(WINDOW_WIDTH - maps[0]->w) / 2 + 3, 3 * WINDOW_HEIGHT / 4 - 3 * maps[0]->h / 2 + 11, 0, 0};
            rects[1] = {(WINDOW_WIDTH - maps[1]->w) / 2 + 3, 3 * WINDOW_HEIGHT / 4 + maps[1]->h / 2, 0, 0};
            break;
        case 3:
            rects[0] = {(WINDOW_WIDTH - maps[0]->w) / 2 + 3, 5 * WINDOW_HEIGHT / 8 - maps[0]->h / 2 + 5, 0, 0};
            rects[1] = {(WINDOW_WIDTH - maps[1]->w) / 2 + 3, 3 * WINDOW_HEIGHT / 4 - maps[1]->h / 2 + 5, 0, 0};
            rects[2] = {(WINDOW_WIDTH - maps[2]->w) / 2 + 3, 7 * WINDOW_HEIGHT / 8 - maps[2]->h / 2 + 5, 0, 0};
            break;
        default:
            break;
    }
}

StartGameView::~StartGameView()
{
    SDL_FreeSurface(up);
    SDL_FreeSurface(down);
    for (unsigned int i = 0; i < mapNumber; i++)
    {
        SDL_FreeSurface(maps[i]);
    }
    delete[] maps;
}

void StartGameView::preRender(unsigned int selectedIndex)
{
    if (selectedIndex < startingMap)
    {
        startingMap--;
    }
    else if (selectedIndex > startingMap + 3)
    {
        startingMap++;
    }
    switch (mapNumber)
    {
        case 1:
            underlineRect = {rects[0].x, rects[0].y + maps[0]->h - 8, maps[0]->w - 6, 6};
            break;
        case 2:
        case 3:
            underlineRect = {rects[selectedIndex].x, rects[selectedIndex].y + maps[selectedIndex]->h - 8, maps[selectedIndex]->w - 6, 6};
            break;
        default:
            rects[0] = {(WINDOW_WIDTH - maps[startingMap]->w) / 2 + 3, 15 * WINDOW_HEIGHT / 24 - maps[startingMap]->h / 2, 0, 0};
            rects[1] = {(WINDOW_WIDTH - maps[startingMap + 1]->w) / 2 + 3, 17 * WINDOW_HEIGHT / 24 - maps[startingMap + 1]->h / 2, 0, 0};
            rects[2] = {(WINDOW_WIDTH - maps[startingMap + 2]->w) / 2 + 3, 19 * WINDOW_HEIGHT / 24 - maps[startingMap + 2]->h / 2, 0, 0};
            rects[3] = {(WINDOW_WIDTH - maps[startingMap + 3]->w) / 2 + 3, 21 * WINDOW_HEIGHT / 24 - maps[startingMap + 3]->h / 2, 0, 0};
            underlineRect = {rects[selectedIndex - startingMap].x, rects[selectedIndex - startingMap].y + maps[selectedIndex]->h - 8, maps[selectedIndex]->w - 6, 6};
    }
}

void StartGameView::reset()
{
    if (resetable)
    {
        MenuView::reset();
        startingMap = 0;
    }
    else
    {
        resetable = true;
    }
}

void StartGameView::render(SDL_Window *window)
{
    SDL_FillRect(SDL_GetWindowSurface(window), &backgroundRect, 0x00FFFFFF);
    SDL_FillRect(SDL_GetWindowSurface(window), &underlineRect, 0x00000000);

    switch (mapNumber)
    {
        case 3:
            SDL_BlitSurface(maps[2], nullptr, SDL_GetWindowSurface(window), &rects[2]);
        case 2:
            SDL_BlitSurface(maps[1], nullptr, SDL_GetWindowSurface(window), &rects[1]);
        case 1:
            SDL_BlitSurface(maps[0], nullptr, SDL_GetWindowSurface(window), &rects[0]);
            break;
        default:
            SDL_BlitSurface(maps[startingMap], nullptr, SDL_GetWindowSurface(window), &rects[0]);
            SDL_BlitSurface(maps[startingMap + 1], nullptr, SDL_GetWindowSurface(window), &rects[1]);
            SDL_BlitSurface(maps[startingMap + 2], nullptr, SDL_GetWindowSurface(window), &rects[2]);
            SDL_BlitSurface(maps[startingMap + 3], nullptr, SDL_GetWindowSurface(window), &rects[3]);
            if (startingMap != 0)
            {
                SDL_BlitSurface(up, nullptr, SDL_GetWindowSurface(window), &upRect);
            }
            if (startingMap != mapNumber - 4)
            {
                SDL_BlitSurface(down, nullptr, SDL_GetWindowSurface(window), &downRect);
            }
    }

    MenuView::render(window);
}
