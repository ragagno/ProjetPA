#include <cstdint>
#include "StartGameModel.h"

StartGameModel::StartGameModel(uint_fast32_t mapNumber)
{
    selectedIndex = 0;
    this->mapNumber = mapNumber;
}

void StartGameModel::init()
{
}

uint_fast32_t StartGameModel::getSelectedIndex() const
{
    return selectedIndex;
}

void StartGameModel::reset()
{
    if (resetable)
    {
        selectedIndex = 0;
    }
    else
    {
        resetable = true;
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