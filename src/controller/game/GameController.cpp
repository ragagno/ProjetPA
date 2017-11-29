#include <iostream>
#include <SDL2/SDL_events.h>
#include "GameController.h"

GameController::GameController::GameController()
{
    nextState = ProximaCentauri::IN_GAME;
    initialized = false;
    ticksFromLastLine = 0;

    model = new GameModel;
    view = new GameView;
}

void GameController::GameController::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game controller is already initialized.\n";
    }
    else
    {
        model->init();
        view->init(renderer);

        initialized = true;
    }
}

GameController::GameController::~GameController()
{
    delete model;
    delete view;
}

void GameController::GameController::tick(long double lag)
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
                        if (model->isPaused() || model->isDefeat() || model->isVictory())
                        {
                            model->up();
                        }
                        break;
                    case SDLK_DOWN:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        if (model->isPaused() || model->isDefeat() || model->isVictory())
                        {
                            model->down();
                        }
                        break;
                    case SDLK_RETURN:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        if (model->isPaused())
                        {
                            switch (model->getSelectedIndex())
                            {
                                case 1:
                                    nextState = ProximaCentauri::TITLE_SCREEN;
                                case 0:
                                    model->flipPause();
                                    ProximaCentauri::getInstance()->setPaused(model->isPaused());
                                    break;
                                default:
                                    std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << model->getSelectedIndex() << "\n";
                                    exit(EXIT_FAILURE);
                            }
                        }
                        else if (model->isVictory())
                        {
                            switch (model->getSelectedIndex())
                            {
                                case 0:
                                    model->reset();
                                    break;
                                case 1:
                                    nextState = ProximaCentauri::TITLE_SCREEN;
                                    break;
                                default:
                                    std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << model->getSelectedIndex() << "\n";
                                    exit(EXIT_FAILURE);
                            }
                        }
                        else if (model->isDefeat())
                        {
                            switch (model->getSelectedIndex())
                            {
                                case 0:
                                    model->reset();
                                    break;
                                case 1:
                                    nextState = ProximaCentauri::TITLE_SCREEN;
                                    break;
                                default:
                                    std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << model->getSelectedIndex() << "\n";
                                    exit(EXIT_FAILURE);
                            }
                        }
                        break;
                    case SDLK_ESCAPE:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        if (!(model->isVictory() || model->isDefeat()))
                        {
                            model->flipPause();
                        }
                        ProximaCentauri::getInstance()->setPaused(model->isPaused());
                        break;
                    default:
                        break;
                }
            }
        }

        if (!(model->isPaused() || model->isDefeat() || model->isVictory()))
        {
            const Uint8 *keys = SDL_GetKeyboardState(nullptr);

            if ((keys[ProximaCentauri::getInstance()->getMoveUpKey()] || keys[ProximaCentauri::getInstance()->getMoveDownKey()] || keys[ProximaCentauri::getInstance()->getMoveLeftKey()] || keys[ProximaCentauri::getInstance()->getMoveRightKey()]) && !((keys[ProximaCentauri::getInstance()->getMoveUpKey()] && keys[ProximaCentauri::getInstance()->getMoveDownKey()]) || (keys[ProximaCentauri::getInstance()->getMoveLeftKey()] && keys[ProximaCentauri::getInstance()->getMoveRightKey()])))
            {
                model->getPlayer().accelerate();
                lastUp = static_cast<bool>(keys[ProximaCentauri::getInstance()->getMoveUpKey()]);
                lastDown = static_cast<bool>(keys[ProximaCentauri::getInstance()->getMoveDownKey()]);
                lastLeft = static_cast<bool>(keys[ProximaCentauri::getInstance()->getMoveLeftKey()]);
                lastRight = static_cast<bool>(keys[ProximaCentauri::getInstance()->getMoveRightKey()]);
                model->move(lastUp, lastDown, lastLeft, lastRight, lag);
            }
            else
            {
                if (model->getPlayer().getSpeed() != 0)
                {
                    model->move(lastUp, lastDown, lastLeft, lastRight, lag);
                    model->getPlayer().deccelerate();
                }
            }

            model->tickEntities(lag);

            if (!model->getPlayer().isAlive())
            {
                model->setDefeat();
            }

            ticksFromLastLine += lag;

            if (ticksFromLastLine >= model->getCurrentLine() * TICKS_PER_LINE)
            {
                if (!model->nextLine())
                {
                    if (model->getEntities().empty())
                    {
                        model->setVictory();
                    }
                }
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameController::GameController::render()
{
    if (initialized)
    {
        view->render(model->getPlayer(), model->getEntities());
        if (model->isPaused())
        {
            view->renderPause(model->getSelectedIndex());
        }
        else if (model->isDefeat())
        {
            view->renderDefeat(model->getSelectedIndex());
        }
        else if (model->isVictory())
        {
            view->renderVictory(model->getSelectedIndex());
        }
        if (nextState != ProximaCentauri::IN_GAME)
        {
            ProximaCentauri::getInstance()->setState(nextState);
            nextState = ProximaCentauri::IN_GAME;
            view->reset();
            model->reset();
            ticksFromLastLine = 0;
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game controller is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}