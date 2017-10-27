#include "InGameModel.h"
#include "../../view/View.h"

InGameModel::InGameModel(Level **maps, uint_fast32_t *inGameLevel)
{
    this->maps = maps;
    this->inGameLevel = inGameLevel;
    paused = false;
    selectedIndex = 0;
}

void InGameModel::init()
{
    player.init(WINDOW_WIDTH / 2, 98);
}

uint_fast32_t InGameModel::getSelectedIndex() const
{
    return selectedIndex;
}

bool InGameModel::isPaused() const
{
    return paused;
}

Player *InGameModel::getPlayer()
{
    return &player;
}

void InGameModel::pauseUp()
{
    selectedIndex = (selectedIndex - 1) * -1;
}

void InGameModel::pauseDown()
{
    selectedIndex = (selectedIndex - 1) * -1;
}

void InGameModel::flipPause()
{
    paused = !paused;
}

void InGameModel::reset()
{
    if (resetable)
    {
        selectedIndex = 0;
        paused = false;
    }
    else
    {
        resetable = true;
    }
}

void InGameModel::update(long double tick)
{
    if (paused)
    {
        // TODO: paused
    }
    else
    {
        // TODO: playing
    }
}