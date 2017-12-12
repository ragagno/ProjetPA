#include <iostream>
#include <cmath>
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
    entities = std::vector<Entity *>();
    plasma = std::vector<Plasmaball>();
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
    if (initialized)
    {
        return entities;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

bool GameModel::nextLine()
{
    if (initialized)
    {
        if (ProximaCentauri::getInstance()->getCurrentMap()->getPatternSize() < ++currentLine)
        {
            return false;
        }
        else
        {
            for (uint_fast32_t i = 0, max = ProximaCentauri::getInstance()->getCurrentMap()->getPattern()[currentLine - 1].size(); i < max; ++i)
            {
                if (Entity::exists(ProximaCentauri::getInstance()->getCurrentMap()->getPattern()[currentLine - 1][i]))
                {
                    entities.push_back(new Entity(Entity::getEntity(ProximaCentauri::getInstance()->getCurrentMap()->getPattern()[currentLine - 1][i])));
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
        last_fire += lag;
        if (last_fire >= PROJECTILE_FREQUENCY)
        {
            plasma.emplace_back(true, PROJECTILE_DAMAGE, 0, -PROJECTILE_SPEED, player.getX() + SPACESHIP_WIDTH / 2, player.getY());
            last_fire = 0;
        }
        for (auto it = plasma.begin(); it < plasma.end(); ++it)
        {
            it->move(lag);
            if (it->getX() < 0 || it->getX() > WINDOW_WIDTH || it->getY() < 0 || it->getY() > WINDOW_HEIGHT)
            {
                plasma.erase(it);
                continue;
            }
            if (it->isPlayer())
            {
                for (auto itE = entities.begin(); itE < entities.end(); ++itE)
                {
                    if (it->getX() > (*itE)->getX() && it->getY() > (*itE)->getY() && it->getX() < (*itE)->getX() + SPACESHIP_WIDTH && it->getY() < (*itE)->getY() + SPACESHIP_HEIGHT)
                    {
                        if ((*itE)->damage(PROJECTILE_DAMAGE))
                        {
                            delete *itE;
                            entities.erase(itE);
                        }
                        plasma.erase(it);
                        break;
                    }
                }
            }
            else
            {
                if (it->getX() > player.getX() && it->getY() > player.getY() && it->getX() < player.getX() + SPACESHIP_WIDTH && it->getY() < player.getY() + SPACESHIP_HEIGHT)
                {
                    player.damage(it->getDamages());
                    plasma.erase(it);
                    continue;
                }
            }
        }
        for (auto it = entities.begin(); it < entities.end(); ++it)
        {
            (*it)->move(lag);
            if ((*it)->getY() > static_cast<int_fast32_t>(WINDOW_HEIGHT))
            {
                delete *it;
                entities.erase(it);
                continue;
            }
            else if ((*it)->getX() < player.getX() + static_cast<int_fast32_t>(SPACESHIP_WIDTH) && (*it)->getX() + static_cast<int_fast32_t>(SPACESHIP_WIDTH) > player.getX() && (*it)->getY() < player.getY() + static_cast<int_fast32_t>(SPACESHIP_HEIGHT) && static_cast<int_fast32_t>(SPACESHIP_HEIGHT) + (*it)->getY() > player.getY())
            {
                player.damage((*it)->getDamageHit());
                delete *it;
                entities.erase(it);
                continue;
            }
            int_fast32_t xE = (*it)->getX() + SPACESHIP_WIDTH / 2;
            int_fast32_t yE = (*it)->getY() + SPACESHIP_HEIGHT;
            int_fast32_t xP = player.getX() + SPACESHIP_WIDTH / 2;
            int_fast32_t yP = player.getY() + SPACESHIP_HEIGHT / 2;
            int_fast32_t a = xP - xE;
            int_fast32_t o = yP - yE;
            long double h = sqrt(o * o + a * a);
            switch ((*it)->shoot(lag))
            {
                case Entity::LASER_BEAM + 1:
                    break;
                case Entity::PLASMA_BALL + 1:
                    plasma.emplace_back(false, (*it)->getDamage(), (a / h) * PROJECTILE_SPEED, (o / h) * PROJECTILE_SPEED, xE, (*it)->getY() + SPACESHIP_HEIGHT);
                    break;
                default:
                    break;
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
        last_fire = 0;
        plasma.clear();
        for (auto e : entities)
        {
            delete e;
        }
        entities.clear();
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

const std::vector<Plasmaball> &GameModel::getPlasma() const
{
    if (initialized)
    {
        return plasma;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game model is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}
