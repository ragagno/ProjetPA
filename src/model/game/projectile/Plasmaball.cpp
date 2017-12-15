#include "Plasmaball.h"

Plasmaball::Plasmaball(bool isPlayer, uint_fast32_t damages, long double xVelocity, long double yVelocity, long double x, long double y) : player(isPlayer), damages(damages), xVelocity(xVelocity), yVelocity(yVelocity), x(x), y(y)
{
}

bool Plasmaball::isPlayer() const
{
    return player;
}

uint_fast32_t Plasmaball::getDamages() const
{
    return damages;
}

int_fast32_t Plasmaball::getX() const
{
    return static_cast<uint_fast32_t>(x);
}

int_fast32_t Plasmaball::getY() const
{
    return static_cast<uint_fast32_t>(y);
}

void Plasmaball::move(long double lag)
{
    x += xVelocity * lag;
    y += yVelocity * lag;
}