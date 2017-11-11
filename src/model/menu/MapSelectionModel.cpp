#include <iostream>
#include "MapSelectionModel.h"
#include "../../ProximaCentauri.h"

MapSelectionModel::MapSelectionModel()
{
    initialized = false;
    mapCount = 0;
    selectedIndex = 0;
    startIndex = 0;
}

void MapSelectionModel::init()
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection model is already initialized.\n";
    }
    else
    {
        mapCount = ProximaCentauri::getInstance()->getMapNumber();
        initialized = true;
    }
}

MapSelectionModel::~MapSelectionModel()
{

}

uint_fast32_t MapSelectionModel::getStartIndex() const
{
    if (initialized)
    {
        return startIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

uint_fast32_t MapSelectionModel::getSelectedIndex() const
{
    if (initialized)
    {
        return selectedIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void MapSelectionModel::up()
{
    if (initialized)
    {
        if (selectedIndex != 0)
        {
            selectedIndex--;
            if (selectedIndex < startIndex)
            {
                startIndex--;
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void MapSelectionModel::down()
{
    if (initialized)
    {
        if (selectedIndex != mapCount - 1)
        {
            selectedIndex++;
            if (selectedIndex > startIndex + 3)
            {
                startIndex++;
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void MapSelectionModel::reset()
{
    if (initialized)
    {
        selectedIndex = 0;
        startIndex = 0;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]MapSelection model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}