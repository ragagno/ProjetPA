#include "StartGameModel.h"

void StartGameModel::init()
{
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

void StartGameModel::update(long double tick)
{
}