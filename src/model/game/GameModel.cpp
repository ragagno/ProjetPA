#include <iostream>
#include "GameModel.h"

GameModel::GameModel()
{
    player = Player();
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
        selectedPauseIndex = 0;
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

void GameModel::move(bool up, bool down, bool left, bool right, long double lag)
{
    if (initialized)
    {
        if (up)
        {
            if (left)
            {
                player.ul(lag);
            }
            else if (right)
            {
                player.ur(lag);
            }
            else
            {
                player.u(lag);
            }
        }
        else if (down)
        {
            if (left)
            {
                player.dl(lag);
            }
            else if (right)
            {
                player.dr(lag);
            }
            else
            {
                player.d(lag);
            }
        }
        else{
            if (left)
            {
                player.l(lag);
            }
            else if (right)
            {
                player.r(lag);
            }
        }
        player.normalize();
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
        player = Player();
        selectedPauseIndex = 0;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

Player &GameModel::getPlayer()
{
    if (initialized)
    {
        return player;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}