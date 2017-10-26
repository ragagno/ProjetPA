#include <cstdint>
#include "TitleScreenModel.h"

TitleScreenModel::TitleScreenModel()
{
    selectedIndex = 0;
}

void TitleScreenModel::init()
{

}

uint_fast32_t TitleScreenModel::getSelectedIndex() const
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
    if (resetable)
    {
        selectedIndex = 0;
    }
    else
    {
        resetable = true;
    }
}

void TitleScreenModel::update(long double)
{
}