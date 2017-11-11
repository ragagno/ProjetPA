#include <iostream>
#include <SDL2/SDL_events.h>
#include "MapSelectionController.h"

MapSelectionController::MapSelectionController()
{
    nextState = ProximaCentauri::MAP_SELECTION;
    initialized = false;

    model = new MapSelectionModel;
    view = new MapSelectionView;
}

void MapSelectionController::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection controller is already initialized.\n";
    }
    else
    {
        model->init();
        view->init(renderer);

        initialized = true;
    }
}

MapSelectionController::~MapSelectionController()
{
    delete model;
    delete view;
}

void MapSelectionController::tick(long double)
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
                        if (ProximaCentauri::getInstance()->getMaps()[model->getSelectedIndex()].loadPattern())
                        {
                            ProximaCentauri::getInstance()->setCurrentMap(model->getSelectedIndex());
                            nextState = ProximaCentauri::IN_GAME;
                        }
                        break;
                    case SDLK_ESCAPE:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        nextState = ProximaCentauri::TITLE_SCREEN;
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void MapSelectionController::render()
{
    if (initialized)
    {
        view->render(model->getSelectedIndex(), model->getStartIndex());
        if (nextState != ProximaCentauri::MAP_SELECTION)
        {
            ProximaCentauri::getInstance()->setState(nextState);
            nextState = ProximaCentauri::MAP_SELECTION;
            model->reset();
            view->reset();
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}