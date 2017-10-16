#include <iostream>
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

void TitleScreenModel::reset()
{
    selectedIndex = 0;
}

void TitleScreenModel::update(const long double tick)
{
}

void TitleScreenModel::up()
{
    selectedIndex = selectedIndex == 0 ? 2 : selectedIndex - 1;
}

void TitleScreenModel::down()
{
    selectedIndex = selectedIndex == 2 ? 0 : selectedIndex + 1;
}
