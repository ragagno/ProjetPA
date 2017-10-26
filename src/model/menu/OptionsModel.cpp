#include <fstream>
#include <iostream>
#include "OptionsModel.h"

OptionsModel::OptionsModel()
{
    music = false;
    sound = false;
    selectedLayout = 0;
    selectedIndex = 0;
}

void OptionsModel::init()
{
    std::ifstream fin("options");

    if (fin.is_open())
    {
        music = fin.get() == 49;
        sound = fin.get() == 49;
        selectedLayout = static_cast<uint_fast32_t >(fin.get() % 48);
        fin.close();
    }
    else
    {
        std::cerr << "Error while loading the options.\n";
        exit(EXIT_FAILURE);
    }

    selectedIndex = 0;
}

uint_fast32_t OptionsModel::getSelectedIndex() const
{
    return selectedIndex;
}

uint_fast32_t OptionsModel::getSelecedLayout() const
{
    return selectedLayout;
}

bool OptionsModel::isMusicOn()
{
    return music;
}

bool OptionsModel::isSoundOn()
{
    return sound;
}

void OptionsModel::reset()
{
    if (resetable)
    {
        selectedIndex = 0;

        std::ofstream fout("options");

        if (fout.is_open())
        {
            fout << (music ? '1' : '0');
            fout << (sound ? '1' : '0');
            fout << (selectedLayout == 0 ? '0' : selectedLayout == 1 ? '1' : '2');
            fout.close();
        }
        else
        {
            std::cerr << "Error while saving the options.\n";
        }
    }
    else
    {
        resetable = true;
    }
}

void OptionsModel::update(long double)
{
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

void OptionsModel::nextLayout()
{
    selectedLayout = selectedLayout == 2 ? 0 : selectedLayout + 1;
}

void OptionsModel::previousLayout()
{
    selectedLayout = selectedLayout == 0 ? 2 : selectedLayout - 1;
}