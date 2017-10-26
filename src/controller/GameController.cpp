#include <dirent.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "GameController.h"
#include "menu/TitleScreenController.h"
#include "menu/StartGameController.h"
#include "menu/OptionsController.h"
#include "game/InGameController.h"

GameController::GameController()
{
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

    if (mapNumber == 0)
    {
        std::cerr << "No map could be found." << std::endl;
        exit(EXIT_FAILURE);
    }

    maps = new Level[mapNumber]();

    for (unsigned int i = 0; i < mapNumber; i++)
    {
        maps[i].setFileName(temp[i]);
    }

    inGameLevel = new unsigned int;

    controllers[TITLE_SCREEN] = new TitleScreenController(&looping, &state);
    models[TITLE_SCREEN] = controllers[TITLE_SCREEN]->getModel();
    views[TITLE_SCREEN] = controllers[TITLE_SCREEN]->getView();

    controllers[START_GAME] = new StartGameController(&state, mapNumber, &maps, inGameLevel);
    models[START_GAME] = controllers[START_GAME]->getModel();
    views[START_GAME] = controllers[START_GAME]->getView();

    controllers[OPTIONS] = new OptionsController(&state);
    models[OPTIONS] = controllers[OPTIONS]->getModel();
    views[OPTIONS] = controllers[OPTIONS]->getView();

    controllers[IN_GAME] = new InGameController(&state, &maps, inGameLevel);
    models[IN_GAME] = controllers[IN_GAME]->getModel();
    views[IN_GAME] = controllers[IN_GAME]->getView();
}

void GameController::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cerr << "Error while initializing SDL." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "Error while initializing SDL_ttf." << std::endl;
        std::cerr << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) == -1)
    {
        std::cerr << "Error while initializing SDL_image." << std::endl;
        std::cerr << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    freq = SDL_GetPerformanceFrequency() / 1000;

    for (unsigned int i = 0; i < mapNumber; i++)
    {
        maps[i].init();
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

    state = TITLE_SCREEN;

    controllers[TITLE_SCREEN]->init();
    controllers[START_GAME]->init();
    controllers[OPTIONS]->init();
    controllers[IN_GAME]->init();
}

GameController::~GameController()
{
    delete inGameLevel;
    for (auto &controller : controllers)
    {
        delete controller;
    }
    delete[] maps;
}

unsigned long long GameController::getTicks()
{
    return SDL_GetPerformanceCounter() / freq;
}

void GameController::start()
{
    SDL_ShowWindow(window);

    looping = true;

    loop();
}

void GameController::shutdown()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void GameController::loop()
{
    unsigned long long lastTime = 0;
    unsigned long long lastRenderTime = 0;
    unsigned long long currentTime = 0;
    unsigned long long elapsedTime = 0;
    long double lag = 0;

    while (looping)
    {
        currentTime = getTicks();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        lag += elapsedTime;

        State tempState = state;
        controllers[state]->tick(lag / MS_PER_UPDATE);

        if (getTicks() - lastRenderTime < 16)
        {
            SDL_Delay(static_cast<Uint32>(16 - currentTime + lastRenderTime));
        }

        lastRenderTime = getTicks();

        views[tempState]->render(window);
        SDL_UpdateWindowSurface(window);

        if (tempState != state)
        {
            models[tempState]->reset();
            views[tempState]->reset();
        }
    }
}