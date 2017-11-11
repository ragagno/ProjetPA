#include <iostream>
#include "TitleScreenModel.h"

TitleScreenModel::TitleScreenModel()
{
    initialized = false;
    selectedIndex = 0;
}

void TitleScreenModel::init()
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen model is already initialized.\n";
    }
    else
    {
        initialized = true;
    }
}

TitleScreenModel::~TitleScreenModel()
{

}

uint_fast32_t TitleScreenModel::getSelectedIndex() const
{
    if (initialized)
    {
        return selectedIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void TitleScreenModel::up()
{
    if (initialized)
    {
        if (selectedIndex == 0)
        {
            selectedIndex = 2;
        }
        else
        {
            selectedIndex--;
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void TitleScreenModel::down()
{
    if (initialized)
    {
        if (selectedIndex == 2)
        {
            selectedIndex = 0;
        }
        else
        {
            selectedIndex++;
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void TitleScreenModel::reset()
{
    if (initialized)
    {
        selectedIndex = 0;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]TitleScreen model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}