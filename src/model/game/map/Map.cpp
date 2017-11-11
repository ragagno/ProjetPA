#include <iostream>
#include <fstream>
#include <utility>
#include <limits>
#include <vector>
#include "Map.h"

Map::Map()
{
    patternSize = 0;
    pattern = nullptr;
}

void Map::loadName(std::string mapName)
{
    fileName = std::move(mapName);

    std::ifstream fin("maps/" + fileName);

    if (fin.is_open())
    {
        std::getline(fin, this->mapName);

        for (char &i : this->mapName)
        {
            if ((i < 65 || i > 122 || (i > 90 && i < 97)) && i != 32)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Title of map " << fileName << " is invalid.\n";
                exit(EXIT_FAILURE);
            }
            if (i > 89)
            {
                i -= 32;
            }
        }

        if (this->mapName.length() == 0)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Title of map " << fileName << " is invalid.\n";
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Title of map " << fileName << " could not be retrieved.\n";
        exit(EXIT_FAILURE);
    }

    fin.close();
}

Map::~Map()
{
    delete[] pattern;
}

const std::string &Map::getMapName() const
{
    if (mapName.length() != 0)
    {
        return mapName;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Map name is not loaded.\n";
        exit(EXIT_FAILURE);
    }
}

uint_fast32_t Map::getPatternSize() const
{
    if (patternSize != 0)
    {
        return patternSize;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Map is not loaded.\n";
        exit(EXIT_FAILURE);
    }
}

std::string *Map::getPattern() const
{
    if (patternSize != 0)
    {
        return pattern;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Map is not loaded.\n";
        exit(EXIT_FAILURE);
    }
}

bool Map::loadPattern()
{
    if (patternSize == 0)
    {
        std::ifstream fin("maps/" + fileName);

        if (fin.is_open())
        {
            fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string line;
            std::vector<std::string> temp;

            std::getline(fin, line);
            if (line.length() == 0 || fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Map file is invalid.\n";
                fin.close();
                return false;
            }

            while (!fin.eof())
            {
                std::getline(fin, line);
                if (line.length() != 16)
                {
                    std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Map file is invalid.\n";
                    fin.close();
                    return false;
                }

                patternSize++;

                temp.push_back(line);
            }

            pattern = new std::string[patternSize];
            for (uint_fast32_t i = 0; i < patternSize; i++)
            {
                pattern[i] = temp[i];
            }
        }
        else
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Map could not be loaded.\n";
            fin.close();
            return false;
        }

        fin.close();
    }
    return true;
}