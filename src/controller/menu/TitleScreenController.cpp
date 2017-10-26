#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_events.h>
#include "TitleScreenController.h"

TitleScreenController::TitleScreenController(bool *looping, GameController::State *state)
{
    this->looping = looping;
    this->state = state;
}

void TitleScreenController::init()
{
    model.init();
    view.init();
}

Model *TitleScreenController::getModel()
{
    return &model;
}

View *TitleScreenController::getView()
{
    return &view;
}

void TitleScreenController::tick(long double ticks)
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
                    switch (model.getSelectedIndex())
                    {
                        case 0:
                            *state = GameController::START_GAME;
                            break;
                        case 1:
                            model.setResetable(false);
                            *state = GameController::OPTIONS;
                            break;
                        case 2:
                            *looping = false;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
    }
    model.update(ticks);
    view.preRender(model.getSelectedIndex());
}