#include "OptionsController.h"

OptionsController::OptionsController(GameController::State *state)
{
    this->state = state;
}

void OptionsController::init()
{
    model.init();
    view.init();
}

Model *OptionsController::getModel()
{
    return &model;
}

View *OptionsController::getView()
{
    return &view;
}

void OptionsController::tick(const long double ticks)
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
                case SDLK_LEFT:
                    model.previousLayout();
                    break;
                case SDLK_RIGHT:
                    model.nextLayout();
                    break;
                case SDLK_RETURN:
                    switch (model.getSelectedIndex())
                    {
                        case 0:
                            model.flipMusic();
                            break;
                        case 1:
                            model.flipSound();
                            break;
                        case 2:
                            model.nextLayout();
                            break;
                        case 3:
                            *state = GameController::TITLE_SCREEN;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDLK_ESCAPE:
                    *state = GameController::TITLE_SCREEN;
                    break;
                default:
                    break;
            }
        }
    }
    view.preRender(model.isMusicOn(), model.isSoundOn(), model.getSelectedIndex(), model.getSelecedLayout());
    model.update(ticks);
}