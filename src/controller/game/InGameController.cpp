#include "InGameController.h"

InGameController::InGameController(GameController::State *state, Level **maps, uint_fast32_t *inGameLevel) : model(maps, inGameLevel)
{
    this->state = state;
}

void InGameController::init()
{
    model.init();
    view.init();
}

Model *InGameController::getModel()
{
    return &model;
}

View *InGameController::getView()
{
    return &view;
}

void InGameController::tick(long double ticks)
{
    if (model.isPaused())
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
                    case SDLK_UP:
                        model.pauseUp();
                        break;
                    case SDLK_DOWN:
                        model.pauseDown();
                        break;
                    case SDLK_RETURN:
                        switch (model.getSelectedIndex())
                        {
                            case 0:
                                model.flipPause();
                                break;
                            case 1:
                                *state = GameController::TITLE_SCREEN;
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDLK_ESCAPE:
                        model.flipPause();
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        SDL_Event event = {};
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if (event.key.repeat)
                        {
                            continue;
                        }
                        model.flipPause();
                        break;
                    default:
                        break;
                }
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(nullptr);

        if (state[SDL_SCANCODE_UP])
        {
            model.getPlayer()->up(ticks);
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            model.getPlayer()->down(ticks);
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            model.getPlayer()->left(ticks);
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            model.getPlayer()->right(ticks);
        }
    }
    model.update(ticks);
    if (model.isPaused())
    {
        view.preRenderPause(model.getSelectedIndex());
    }
    else
    {
        view.preRenderPlaying(model.getPlayer());
    }
}