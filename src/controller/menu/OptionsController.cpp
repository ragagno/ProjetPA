#include <iostream>
#include <SDL2/SDL_events.h>
#include "OptionsController.h"

OptionsController::OptionsController()
{
    nextState = ProximaCentauri::OPTIONS;
    initialized = false;

    model = new OptionsModel;
    view = new OptionsView;
}

void OptionsController::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options controller is already initialized.\n";
    }
    else
    {
        model->init();
        view->init(renderer);

        initialized = true;
    }
}

OptionsController::~OptionsController()
{
    delete model;
    delete view;
}

void OptionsController::tick(long double)
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
                    case SDLK_LEFT:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        switch (model->getSelectedIndex())
                        {
                            case 0:
                                model->flipMusic();
                                break;
                            case 1:
                                model->flipSound();
                                break;
                            case 2:
                                model->previousLayout();
                                break;
                            case 3:
                                // DO NOTHING
                                break;
                            default:
                                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected selected index: " << model->getSelectedIndex() << "\n";
                                exit(EXIT_FAILURE);
                        }
                        break;
                    case SDLK_RIGHT:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        switch (model->getSelectedIndex())
                        {
                            case 0:
                                model->flipMusic();
                                break;
                            case 1:
                                model->flipSound();
                                break;
                            case 2:
                                model->nextLayout();
                                break;
                            case 3:
                                // DO NOTHING
                                break;
                            default:
                                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << model->getSelectedIndex() << "\n";
                                exit(EXIT_FAILURE);
                        }
                        break;
                    case SDLK_RETURN:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        switch (model->getSelectedIndex())
                        {
                            case 0:
                                model->flipMusic();
                                break;
                            case 1:
                                model->flipSound();
                                break;
                            case 2:
                                model->nextLayout();
                                break;
                            case 3:
                                model->saveOptions();
                                nextState = ProximaCentauri::TITLE_SCREEN;
                                break;
                            default:
                                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << model->getSelectedIndex() << "\n";
                                exit(EXIT_FAILURE);
                        }
                        break;
                    case SDLK_ESCAPE:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        model->saveOptions();
                        nextState = ProximaCentauri::TITLE_SCREEN;
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsController::render()
{
    if (initialized)
    {
        view->render(model->getSelectedIndex(), model->isMusicOn(), model->isSoundon(), model->getLayout());
        if (nextState != ProximaCentauri::OPTIONS)
        {
            ProximaCentauri::getInstance()->setState(nextState);
            nextState = ProximaCentauri::OPTIONS;
            model->reset();
            view->reset();
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}