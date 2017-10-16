#include <dirent.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "GameController.h"
#include "../view/menu/TitleScreenView.h"
#include "../view/menu/StartGameView.h"
#include "../model/menu/TitleScreenModel.h"

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

    models[TITLE_SCREEN] = new TitleScreenModel();
    views[TITLE_SCREEN] = new TitleScreenView(models[TITLE_SCREEN]);

    views[START_GAME] = new StartGameView();
}

unsigned long long GameController::getTicks()
{
    return SDL_GetPerformanceCounter() / freq;
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

    views[TITLE_SCREEN]->init();
    views[START_GAME]->init();
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
    double lag = 0;
    SDL_Event event;

    while (looping)
    {
        currentTime = getTicks();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        lag += elapsedTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                models[TITLE_SCREEN]->update(&event);
            }
        }

        while (lag >= MS_PER_UPDATE)
        {
            // TODO: game logic update
            lag -= MS_PER_UPDATE;
        }

        if (getTicks() - lastRenderTime < 16)
        {
            SDL_Delay(static_cast<Uint32>(16 - currentTime + lastRenderTime));
        }

        lastRenderTime = getTicks();

        views[state]->render(window);
        SDL_UpdateWindowSurface(window);
    }
}

GameController::~GameController()
{
    for (auto &view : views)
    {
        delete view;
    }
    // models are delete by view destructor
    delete[] maps;
}