#include <iostream>
#include "OptionsModel.h"

void OptionsModel::init()
{
    music = true;
    sound = true;
}

void OptionsModel::reset()
{
    selectedIndex = 0;
}

void OptionsModel::update(long double tick)
{
}

bool OptionsModel::isMusicOn()
{
    return music;
}

bool OptionsModel::isSoundOn()
{
    return sound;
}

void OptionsModel::up()
{
    selectedIndex = selectedIndex == 0 ? 3 : selectedIndex - 1;
}

void OptionsModel::down()
{
    selectedIndex = selectedIndex == 3 ? 0 : selectedIndex + 1;
}

void OptionsModel::flipMusic()
{
    music = !music;
}

void OptionsModel::flipSound()
{
    sound = !sound;
}

unsigned int OptionsModel::getSelectedIndex() const
{
    return selectedIndex;
}