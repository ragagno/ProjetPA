#include "ControlsController.h"

Model *ControlsController::getModel()
{
    return &model;
}

View *ControlsController::getView()
{
    return &view;
}

void ControlsController::init()
{
    model.init();
    view.init();
}

void ControlsController::tick(long double ticks)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    *state = GameController::OPTIONS;
                    break;
                default:
                    break;
            }
        }
    }
}

ControlsController::ControlsController(GameController::State *state)
{
    this->state = state;
}