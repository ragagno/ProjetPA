#include <iostream>
#include "StartGameController.h"

StartGameController::StartGameController(GameController::State *state, unsigned int mapNumber, Level **mapsLevel)
        : model(mapNumber), view(mapNumber, mapsLevel)
{
    this->state = state;
}

void StartGameController::init()
{
    model.init();
    view.init();
}

Model *StartGameController::getModel()
{
    return &model;
}

View *StartGameController::getView()
{
    return &view;
}

void StartGameController::tick(long double)
{
    SDL_Event event = {};
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat)
            {
                continue;
            }
            switch (event.key.keysym.sym)
            {
                case SDLK_DOWN:
                    model.down();
                    break;
                case SDLK_UP:
                    model.up();
                    break;
                case SDLK_RETURN:
                    // TODO: playing
                    break;
                case SDLK_ESCAPE:
                    *state = GameController::TITLE_SCREEN;
                    break;
                default:
                    break;
            }
        }
    }
    view.preRender(model.getSelectedIndex());
}