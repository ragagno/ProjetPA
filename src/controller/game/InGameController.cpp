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
    }
    model.update(ticks);
    view.preRender(model.isPaused(), model.getSelectedIndex());
}