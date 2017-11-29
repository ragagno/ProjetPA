#include <iostream>
#include "GameModel.h"
#include "../../ProximaCentauri.h"

GameModel::GameModel()
{
    player = Player();
    initialized = false;
    paused = false;
    victory = false;
    defeat = false;
    selectedPauseIndex = 0;
    currentLine = 0;
}

void GameModel::init()
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is already initialized.\n";
    }
    else
    {
        Entity::init();
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

uint_fast32_t GameModel::getCurrentLine() const
{
    if (initialized)
    {
        return currentLine;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

bool GameModel::isDefeat() const
{
    if (initialized)
    {
        return defeat;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

bool GameModel::isVictory() const
{
    if (initialized)
    {
        return victory;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameModel::setDefeat()
{
    if (initialized)
    {
        defeat = true;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameModel::setVictory()
{
    if (initialized)
    {
        victory = true;
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

std::vector<Entity *> GameModel::getEntities()
{
    return entities;
}

bool GameModel::nextLine()
{
    if (initialized)
    {
        if (ProximaCentauri::getInstance()->getCurrentMap().getPatternSize() < ++currentLine)
        {
            return false;
        }
        else
        {
            for (uint_fast32_t i = 0, max = ProximaCentauri::getInstance()->getCurrentMap().getPattern()[currentLine - 1].size(); i < max; ++i)
            {
                if (Entity::exists(ProximaCentauri::getInstance()->getCurrentMap().getPattern()[currentLine - 1][i]))
                {
                    entities.push_back(new Entity(Entity::getEntity(ProximaCentauri::getInstance()->getCurrentMap().getPattern()[currentLine - 1][i])));
                    entities[entities.size() - 1]->setX(i);
                }
            }
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
    return true;
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

void GameModel::tickEntities(long double lag)
{
    if (initialized)
    {
        for (auto it = entities.begin(); it < entities.end(); it++)
        {
            (*it)->move(lag);
            (*it)->shoot(lag);
            if ((*it)->getY() > static_cast<int_fast32_t>(WINDOW_HEIGHT))
            {
                delete *it;
                entities.erase(it);
            }
            else if ((*it)->getX() < player.getX() + static_cast<int_fast32_t>(SPACESHIP_WIDTH) && (*it)->getX() + static_cast<int_fast32_t>(SPACESHIP_WIDTH) > player.getX() && (*it)->getY() < player.getY() + static_cast<int_fast32_t>(SPACESHIP_HEIGHT) && static_cast<int_fast32_t>(SPACESHIP_HEIGHT) + (*it)->getY() > player.getY())
            {
                player.damage((*it)->getDamageHit());
                delete *it;
                entities.erase(it);
            }
        }

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
        else
        {
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
        defeat = false;
        victory = false;
        player = Player();
        selectedPauseIndex = 0;
        currentLine = 0;
        for (auto e : entities)
        {
            delete e;
        }
        entities = std::vector<Entity *>();
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