#include <iostream>
#include <SDL2/SDL_events.h>
#include "TitleScreenController.h"

TitleScreenController::TitleScreenController()
{
    nextState = ProximaCentauri::TITLE_SCREEN;
    initialized = false;

    model = new TitleScreenModel;
    view = new TitleScreenView;
}

void TitleScreenController::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen controller is already initialized.\n";
    }
    else
    {
        model->init();
        view->init(renderer);

        initialized = true;
    }
}

TitleScreenController::~TitleScreenController()
{
    delete model;
    delete view;
}

void TitleScreenController::tick(long double)
{
    if (initialized)
    {
        SDL_Event event{};

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        model->up();
                        break;
                    case SDLK_DOWN:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        model->down();
                        break;
                    case SDLK_RETURN:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        switch (model->getSelectedIndex())
                        {
                            case 0:
                                nextState = ProximaCentauri::MAP_SELECTION;
                                break;
                            case 1:
                                nextState = ProximaCentauri::OPTIONS;
                                break;
                            case 2:
                                ProximaCentauri::getInstance()->stopGame();
                                break;
                            default:
                                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << model->getSelectedIndex() << "\n";
                                exit(EXIT_FAILURE);
                        }
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void TitleScreenController::render()
{
    if (initialized)
    {
        view->render(model->getSelectedIndex());
        if (nextState != ProximaCentauri::TITLE_SCREEN)
        {
            ProximaCentauri::getInstance()->setState(nextState);
            nextState = ProximaCentauri::TITLE_SCREEN;
            view->reset();
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}