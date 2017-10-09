#include <dirent.h>
#include <iostream>
#include <vector>
#include "Game.h"

Game::Game()
{
    looping = false;
    mapNumber = 0;

    struct dirent *ep;
    std::vector<std::string> temp;
    DIR *dp;

    dp = opendir("maps/");

    if (dp != nullptr)
    {
        while ((ep = readdir(dp)))
        {
            if (ep->d_name[0] == '.')
            {
                continue;
            }
            mapNumber++;
            temp.push_back(static_cast<std::string>(ep->d_name));
        }
        closedir(dp);
    }
    else
    {
        std::cerr << "Error while counting maps.\n";
        exit(EXIT_FAILURE);
    }

    maps = new Level[mapNumber]();

    for (unsigned int i = 0; i < mapNumber; i++)
    {
        maps[i].setFileName(temp[i]);
    }
}

void Game::init()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

void Game::start()
{
    looping = true;

    window = SDL_CreateWindow("Proxima Centauri", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(window);

    loop();
}

void Game::shutdown()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::loop()
{
    int lastTime = 0;
    int lastRenderTime = 0;
    double lag = 0;

    while (looping)
    {
        int currentTime = SDL_GetTicks();
        int elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        lag += elapsedTime;

        // TODO: process input

        while (lag >= MS_PER_UPDATE)
        {
            // TODO: game logic update
            lag -= MS_PER_UPDATE;
        }

        if (SDL_GetTicks() - lastRenderTime < 16)
        {
            SDL_Delay(16 - SDL_GetTicks() + lastRenderTime);
        }

        lastRenderTime = SDL_GetTicks();
        // TODO: render(lag / MS_PER_UPDATE)

    }
}

Game::~Game()
{
    delete[] maps;
}