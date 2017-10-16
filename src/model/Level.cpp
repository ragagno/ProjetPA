#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include "Level.h"

Level::Level()
{
    pattern = nullptr;
}

void Level::init()
{
    std::ifstream fin("maps/" + this->fileName);

    if (fin.is_open())
    {
        std::getline(fin, name);

        if (name.length() == 0)
        {
            std::cerr << "Error while loading " + this->fileName + ": file is invalid.\n";
            exit(EXIT_FAILURE);
        }

        fin.close();
    }
    else
    {
        std::cerr << "Error while getting a map name in its file.\n";
        exit(EXIT_FAILURE);
    }
}

void Level::setFileName(const std::string &fileName)
{
    this->fileName = fileName;
}

void Level::loadLevel()
{
    delete pattern;
    patternSize = 0;

    std::ifstream fin("maps/" + this->fileName);

    if (fin.is_open())
    {
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string line;
        std::vector<std::string> temp;

        std::getline(fin, line);
        if (line.length() == 0 || fin.eof())
        {
            std::cerr << "Error while loading " + this->fileName + ": file is invalid.\n";
            exit(EXIT_FAILURE);
        }

        try
        {
            repeatPattern = static_cast<uint32_t>(std::stoi(line));
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << "Error while loading " + this->fileName + ": file is invalid.\n";
            exit(EXIT_FAILURE);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << "Error while loading " + this->fileName + ": file is invalid.\n";
            exit(EXIT_FAILURE);
        }

        while (!fin.eof())
        {
            std::getline(fin, line);
            if (line.length() != 16)
            {
                std::cerr << "Error while loading " + this->fileName + ": file is invalid.\n";
                exit(EXIT_FAILURE);
            }

            patternSize++;

            temp.push_back(line);
        }

        pattern = new std::string[patternSize];
        for (uint32_t i = 0; i < patternSize; i++)
        {
            pattern[i] = temp[i];
        }
    }
    else
    {
        std::cerr << "Error while loading the map.\n";
        exit(EXIT_FAILURE);
    }
}

Level::~Level()
{
    delete[] pattern;
}