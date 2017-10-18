#include "StartGameController.h"

StartGameController::StartGameController(GameController::State *state)
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

void StartGameController::tick(long double ticks)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    *state = GameController::TITLE_SCREEN;
                    break;
                default:
                    break;
            }
        }
    }
}