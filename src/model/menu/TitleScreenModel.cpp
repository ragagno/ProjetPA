#include <iostream>
#include "TitleScreenModel.h"

TitleScreenModel::TitleScreenModel()
{
    selectedIndex = 0;
}

unsigned int TitleScreenModel::getSelectedIndex() const
{
    return selectedIndex;
}

void TitleScreenModel::reset()
{
    selectedIndex = 0;
}

void TitleScreenModel::update(SDL_Event *event)
{
    if (!event->key.repeat)
    {
        switch (event->key.keysym.sym)
        {
            case SDLK_DOWN:
                selectedIndex = selectedIndex == 2 ? 0 : selectedIndex + 1;
                break;
            case SDLK_UP:
                selectedIndex = selectedIndex == 0 ? 2 : selectedIndex - 1;
                break;
            default:
                break;
        }
    }
}
