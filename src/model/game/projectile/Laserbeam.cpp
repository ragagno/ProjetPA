#include "Laserbeam.h"
#include "../../../ProximaCentauri.h"

Laserbeam::Laserbeam(Entity *origin, Player *player) : origin(origin), player(player)
{
    alive = true;
    ticksFromBirth = 0;
}

uint_fast32_t Laserbeam::getX() const
{
    return origin->getX() + SPACESHIP_WIDTH / 2;
}

uint_fast32_t Laserbeam::getY() const
{
    return origin->getY() + SPACESHIP_HEIGHT - 1;
}

uint_fast32_t Laserbeam::getL() const
{
    return (static_cast<int_fast32_t>(origin->getX() + SPACESHIP_WIDTH / 2) > player->getX() && (origin->getX() + SPACESHIP_WIDTH / 2) < (player->getX() + SPACESHIP_WIDTH)) && (player->getY() > static_cast<int_fast32_t>(getY())) ? static_cast<uint_fast32_t>(player->getY() - origin->getY() - 42) : (WINDOW_HEIGHT - (origin->getY() + SPACESHIP_HEIGHT));
}

uint_fast32_t Laserbeam::getDamages() const
{
    return origin->getDamage();
}

void Laserbeam::kill()
{
    alive = false;
}

bool Laserbeam::tick(long double lag)
{
    ticksFromBirth += lag;
    return !alive || ticksFromBirth > LASER_LIFE;
}

void Laserbeam::unsetOrigin()
{
    origin->terminateLaser();
}

bool Laserbeam::isAlive() const
{
    return alive;
}
