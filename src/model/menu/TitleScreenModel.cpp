#include "TitleScreenModel.h"

TitleScreenModel::TitleScreenModel()
{
    selectedIndex = 0;
}

void TitleScreenModel::init()
{

}

unsigned int TitleScreenModel::getSelectedIndex() const
{
    return selectedIndex;
}

void TitleScreenModel::up()
{
    selectedIndex = selectedIndex == 0 ? 2 : selectedIndex - 1;
}

void TitleScreenModel::down()
{
    selectedIndex = selectedIndex == 2 ? 0 : selectedIndex + 1;
}


void TitleScreenModel::reset()
{
    if (isResetable())
    {
        selectedIndex = 0;
    }
    else
    {
        setResetable(true);
    }
}

void TitleScreenModel::update(const long double tick)
{
}