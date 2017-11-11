#include <iostream>
#include "GameModel.h"

GameModel::GameModel()
{
    initialized = false;
    paused = false;
    selectedPauseIndex = 0;
}

void GameModel::init()
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is already initialized.\n";
    }
    else
    {
        initialized = true;
    }
}

GameModel::~GameModel()
{

}

bool GameModel::isPaused() const
{
    if (initialized)
    {
        return paused;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

uint_fast32_t GameModel::getSelectedIndex() const
{
    if (initialized)
    {
        return selectedPauseIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameModel::flipPause()
{
    if (initialized)
    {
        paused = !paused;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameModel::up()
{
    if (initialized)
    {
        selectedPauseIndex = 1 - selectedPauseIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameModel::down()
{
    if (initialized)
    {
        selectedPauseIndex = 1 - selectedPauseIndex;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameModel::reset()
{
    if (initialized)
    {
        paused = false;
        selectedPauseIndex = 0;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}