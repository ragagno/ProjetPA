#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "MapSelectionView.h"
#include "../../ProximaCentauri.h"

MapSelectionView::MapSelectionView()
{
    initialized = false;

    renderer = nullptr;
}

void MapSelectionView::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection view is already initialized.\n";
    }
    else
    {
        MenuView::init(renderer);

        auto mapObjects = ProximaCentauri::getInstance()->getMaps();
        mapCount = ProximaCentauri::getInstance()->getMapNumber();

        mapSrcRect = new SDL_Rect[mapCount];
        maps = new SDL_Texture *[mapCount];

        TTF_Font *munro = TTF_OpenFont("resources/munro.ttf", 64);
        if (munro == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Resource munro.ttf could not be loaded.\n";
            exit(EXIT_FAILURE);
        }

        for (uint_fast32_t i = 0; i < mapCount; i++)
        {
            SDL_Surface *mapSurface;
            uint_fast32_t index = 0;
            do
            {
                mapSurface = TTF_RenderUTF8_Blended(munro, mapObjects[i].getMapName().substr(0, mapObjects[i].getMapName().length() - (1 + index++)).c_str(), SDL_Color{0, 0, 0, 255});
            } while (mapSurface->w > WINDOW_WIDTH - 2 * MENU_SPACEING);

            maps[i] = SDL_CreateTextureFromSurface(renderer, mapSurface);

            mapSrcRect[i] = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, mapSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), mapSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

            SDL_FreeSurface(mapSurface);
        }

        int_fast32_t w = 0;
        int_fast32_t h = 0;

        SDL_QueryTexture(ProximaCentauri::getInstance()->getUpArrow(), nullptr, nullptr, &w, &h);
        upDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - w) / 2, static_cast<int_fast32_t>(8 * WINDOW_HEIGHT / 14) - h / 2, w, h};

        SDL_QueryTexture(ProximaCentauri::getInstance()->getDownArrow(), nullptr, nullptr, &w, &h);
        downDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - w) / 2, static_cast<int_fast32_t>(13 * WINDOW_HEIGHT / 14) - h / 2, w, h};

        TTF_CloseFont(munro);
        initialized = true;
    }
}

MapSelectionView::~MapSelectionView()
{
    delete[] mapSrcRect;

    for (uint_fast32_t i = 0; i < mapCount; i++)
    {
        SDL_DestroyTexture(maps[i]);
    }

    delete[] maps;
}

void MapSelectionView::render(uint_fast32_t selectedIndex, uint_fast32_t startIndex) const
{
    if (initialized)
    {
        MenuView::render();

        SDL_Rect backgroundRect{MENU_SPACEING, WINDOW_HEIGHT / 2 + MENU_SPACEING, WINDOW_WIDTH - MENU_SPACEING * 2, WINDOW_HEIGHT / 2 - MENU_SPACEING * 2};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);

        SDL_RenderFillRect(renderer, &backgroundRect);

        SDL_Rect firstDstRect{};
        SDL_Rect secondDstRect{};
        SDL_Rect thirdDstRect{};
        SDL_Rect fourthDstRect{};

        switch (mapCount)
        {
            case 1:
                firstDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex].w) / 2, static_cast<int_fast32_t>(3 * WINDOW_HEIGHT / 4) - mapSrcRect[startIndex].h / 2, mapSrcRect[startIndex].w, mapSrcRect[startIndex].h};

                SDL_RenderCopy(renderer, maps[startIndex], &mapSrcRect[startIndex], &firstDstRect);
                break;
            case 2:
                firstDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex].w) / 2, static_cast<int_fast32_t>(11 * WINDOW_HEIGHT / 16) - mapSrcRect[startIndex].h / 2, mapSrcRect[startIndex].w, mapSrcRect[startIndex].h};
                secondDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex + 1].w) / 2, static_cast<int_fast32_t>(13 * WINDOW_HEIGHT / 16) - mapSrcRect[startIndex + 1].h / 2, mapSrcRect[startIndex].w, mapSrcRect[startIndex].h};

                SDL_RenderCopy(renderer, maps[startIndex], &mapSrcRect[startIndex], &firstDstRect);
                SDL_RenderCopy(renderer, maps[startIndex + 1], &mapSrcRect[startIndex + 1], &secondDstRect);
                break;
            case 3:
                firstDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex].w) / 2, static_cast<int_fast32_t>(5 * WINDOW_HEIGHT / 8) - mapSrcRect[startIndex].h / 2, mapSrcRect[startIndex].w, mapSrcRect[startIndex].h};
                secondDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex + 1].w) / 2, static_cast<int_fast32_t>(6 * WINDOW_HEIGHT / 8) - mapSrcRect[startIndex + 1].h / 2, mapSrcRect[startIndex + 1].w, mapSrcRect[startIndex + 1].h};
                thirdDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex + 2].w) / 2, static_cast<int_fast32_t>(7 * WINDOW_HEIGHT / 8) - mapSrcRect[startIndex + 2].h / 2, mapSrcRect[startIndex + 2].w, mapSrcRect[startIndex + 2].h};

                SDL_RenderCopy(renderer, maps[startIndex], &mapSrcRect[startIndex], &firstDstRect);
                SDL_RenderCopy(renderer, maps[startIndex + 1], &mapSrcRect[startIndex + 1], &secondDstRect);
                SDL_RenderCopy(renderer, maps[startIndex + 2], &mapSrcRect[startIndex + 2], &thirdDstRect);
                break;
            default:
                if (startIndex != 0)
                {
                    SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getUpArrow(), nullptr, &upDstRect);
                }
                if (startIndex != mapCount - 4)
                {
                    SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getDownArrow(), nullptr, &downDstRect);
                }
                firstDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex].w) / 2, static_cast<int_fast32_t>(9 * WINDOW_HEIGHT / 14) - mapSrcRect[startIndex].h / 2, mapSrcRect[startIndex].w, mapSrcRect[startIndex].h};
                secondDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex + 1].w) / 2, static_cast<int_fast32_t>(10 * WINDOW_HEIGHT / 14) - mapSrcRect[startIndex + 1].h / 2, mapSrcRect[startIndex + 1].w, mapSrcRect[startIndex + 1].h};
                thirdDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex + 2].w) / 2, static_cast<int_fast32_t>(11 * WINDOW_HEIGHT / 14) - mapSrcRect[startIndex + 2].h / 2, mapSrcRect[startIndex + 2].w, mapSrcRect[startIndex + 2].h};
                fourthDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - mapSrcRect[startIndex + 3].w) / 2, static_cast<int_fast32_t>(12 * WINDOW_HEIGHT / 14) - mapSrcRect[startIndex + 3].h / 2, mapSrcRect[startIndex + 3].w, mapSrcRect[startIndex + 3].h};

                SDL_RenderCopy(renderer, maps[startIndex], &mapSrcRect[startIndex], &firstDstRect);
                SDL_RenderCopy(renderer, maps[startIndex + 1], &mapSrcRect[startIndex + 1], &secondDstRect);
                SDL_RenderCopy(renderer, maps[startIndex + 2], &mapSrcRect[startIndex + 2], &thirdDstRect);
                SDL_RenderCopy(renderer, maps[startIndex + 3], &mapSrcRect[startIndex + 3], &fourthDstRect);
        }

        SDL_Rect underlineRect{};

        switch (selectedIndex - startIndex)
        {
            case 0:
                underlineRect = {firstDstRect.x, firstDstRect.y + mapSrcRect[selectedIndex].h + static_cast<int_fast32_t>(UNDERLINE_SPACING), mapSrcRect[selectedIndex].w, UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {secondDstRect.x, secondDstRect.y + mapSrcRect[selectedIndex].h + static_cast<int_fast32_t>(UNDERLINE_SPACING), mapSrcRect[selectedIndex].w, UNDERLINE_THICKNESS};
                break;
            case 2:
                underlineRect = {thirdDstRect.x, thirdDstRect.y + mapSrcRect[selectedIndex].h + static_cast<int_fast32_t>(UNDERLINE_SPACING), mapSrcRect[selectedIndex].w, UNDERLINE_THICKNESS};
                break;
            case 3:
                underlineRect = {fourthDstRect.x, fourthDstRect.y + mapSrcRect[selectedIndex].h + static_cast<int_fast32_t>(UNDERLINE_SPACING), mapSrcRect[selectedIndex].w, UNDERLINE_THICKNESS};
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
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void MapSelectionView::reset() const
{
    MenuView::reset();
}