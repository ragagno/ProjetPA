#include <iostream>
#include <fstream>
#include "OptionsModel.h"

OptionsModel::OptionsModel()
{
    initialized = false;
    music = false;
    sound = false;
    layout = WASD;
    selectedIndex = 0;
}

void OptionsModel::init()
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is already initialized.\n";
    }
    else
    {
        std::ifstream fin("options");

        if (fin.is_open())
        {
            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Invalid options file.\n";
            }
            else
            {
                music = fin.get() == 49;
                if (fin.eof())
                {
                    std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Invalid options file.\n";
                }
                else
                {
                    sound = fin.get() == 49;
                    if (fin.eof())
                    {
                        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Invalid options file.\n";
                    }
                    else
                    {
                        switch (fin.get())
                        {
                            case 49:
                                layout = ZQSD;
                                break;
                            case 50:
                                layout = ARROWS;
                                break;
                            case 48:
                            default:
                                layout = WASD;
                        }
                    }
                }
            }
            fin.close();
        }
        else
        {
            std::ofstream fout("options");

            if (fout.is_open())
            {
                fout << "000";
                fout.close();
            }
            else
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Error while creating options file.\n";
            }
        }

        initialized = true;
    }
}

OptionsModel::~OptionsModel()
{

}

bool OptionsModel::isMusicOn() const
{
    if (initialized)
    {
        return music;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

bool OptionsModel::isSoundon() const
{
    if (initialized)
    {
        return sound;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

OptionsModel::KeyboardLayout OptionsModel::getLayout() const
{
    if (initialized)
    {
        return layout;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

uint_fast32_t OptionsModel::getSelectedIndex() const
{
    if (initialized)
    {
        return selectedIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::flipSound()
{
    if (initialized)
    {
        sound = !sound;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::flipMusic()
{
    if (initialized)
    {
        music = !music;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::nextLayout()
{
    if (initialized)
    {
        switch (layout)
        {
            case WASD:
                layout = ZQSD;
                break;
            case ZQSD:
                layout = ARROWS;
                break;
            case ARROWS:
                layout = WASD;
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected layout: " << layout << "\n";
                exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::previousLayout()
{
    if (initialized)
    {
        switch (layout)
        {
            case WASD:
                layout = ARROWS;
                break;
            case ZQSD:
                layout = WASD;
                break;
            case ARROWS:
                layout = ZQSD;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected layout: " << layout << "\n";
                exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::up()
{
    if (initialized)
    {
        if (selectedIndex == 0)
        {
            selectedIndex = 3;
        }
        else
        {
            selectedIndex--;
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::down()
{
    if (initialized)
    {
        if (selectedIndex == 3)
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
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::reset()
{
    if (initialized)
    {
        selectedIndex = 0;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void OptionsModel::saveOptions() const
{
    if (initialized)
    {
        std::ofstream fout("options");

        if (fout.is_open())
        {
            fout << (music ? '1' : '0');
            fout << (sound ? '1' : '0');
            fout << (layout == WASD ? '0' : (layout == ZQSD ? '1' : '2'));
            fout.close();
        }
        else
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not create option file.\n";
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Options model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}