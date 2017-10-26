#include "StartGameController.h"

StartGameController::StartGameController(GameController::State *state, unsigned int mapNumber, Level **maps, unsigned int *inGameLevel) : model(mapNumber), view(mapNumber, maps)
{
    this->maps = maps;
    this->inGameLevel = inGameLevel;
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
            switch (event.key.keysym.sym)
            {
                case SDLK_DOWN:
                    model.down();
                    break;
                case SDLK_UP:
                    model.up();
                    break;
                case SDLK_RETURN:
                    if (event.key.repeat)
                    {
                        continue;
                    }
                    *state = GameController::IN_GAME;
                    *inGameLevel = model.getSelectedIndex();
                    (*maps)[*inGameLevel].loadLevel();
                    break;
                case SDLK_ESCAPE:
                    if (event.key.repeat)
                    {
                        continue;
                    }
                    *state = GameController::TITLE_SCREEN;
                    break;
                default:
                    break;
            }
        }
    }
    view.preRender(model.getSelectedIndex());
}