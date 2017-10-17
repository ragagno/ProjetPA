#include "ControlsModel.h"

void ControlsModel::init()
{
}

void ControlsModel::reset()
{
    if (isResetable())
    {
    }
    else
    {
        setResetable(true);
    }
}

void ControlsModel::update(long double tick)
{
}