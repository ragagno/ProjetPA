#include "StartGameModel.h"

StartGameModel::StartGameModel(unsigned int mapNumber)
{
    selectedIndex = 0;
    this->mapNumber = mapNumber;
}

void StartGameModel::init()
{
}

unsigned int StartGameModel::getSelectedIndex() const
{
    return selectedIndex;
}

void StartGameModel::reset()
{
    if (isResetable())
    {}
    else
    {
        setResetable(true);
    }
}

void StartGameModel::update(long double)
{
}

void StartGameModel::up()
{
    selectedIndex += selectedIndex == 0 ? 0 : -1;
}

void StartGameModel::down()
{
    selectedIndex += selectedIndex == mapNumber - 1 ? 0 : 1;
}