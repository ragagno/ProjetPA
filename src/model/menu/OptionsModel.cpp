#include <fstream>
#include <iostream>
#include "OptionsModel.h"

void OptionsModel::init()
{
    std::ifstream fin("options");

    if (fin.is_open())
    {
        music = fin.get() == 49;
        sound = fin.get() == 49;
        fin.close();
    }
    else
    {
        std::cerr << "Error while loading the options.\n";
        exit(EXIT_FAILURE);
    }

    selectedIndex = 0;
}

void OptionsModel::reset()
{
    if (isResetable())
    {
        selectedIndex = 0;

        std::ofstream fout("options");

        if (fout.is_open())
        {
            fout << music ? '1' : '0';
            fout << sound ? '1' : '0';
            fout.close();
        }
        else
        {
            std::cerr << "Error while saving the options.\n";
            // NO CRASH
        }
    }
    else
    {
        setResetable(true);
    }
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