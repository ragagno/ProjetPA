#include "Player.h"
#include "../../../ProximaCentauri.h"

Player::Player()
{
    x = (WINDOW_WIDTH - SPACESHIP_WIDTH) / 2;
    y = WINDOW_HEIGHT - SPACESHIP_HEIGHT - SPACESHIP_INITIAL_Y;
    speed = 0;
}

Player::~Player()
{

}

uint_fast32_t Player::getX() const
{
    return static_cast<uint_fast32_t>(x);
}

uint_fast32_t Player::getY() const
{
    return static_cast<uint_fast32_t>(y);
}

long double Player::getSpeed() const
{
    return speed;
}

void Player::u(long double lag)
{
    y -= speed * lag;
}

void Player::d(long double lag)
{
    y += speed * lag;
}

void Player::l(long double lag)
{
    x -= speed * lag;
}

void Player::r(long double lag)
{
    x += speed * lag;
}

void Player::ul(long double lag)
{
    u(lag);
    l(lag);
}

void Player::ur(long double lag)
{
    u(lag);
    r(lag);
}

void Player::dl(long double lag)
{
    d(lag);
    l(lag);
}

void Player::dr(long double lag)
{
    d(lag);
    r(lag);
}

void Player::accelerate()
{
    speed += SPACESHIP_ACCELERATION;
    if (speed > SPACESHIP_SPEED)
    {
        speed = SPACESHIP_SPEED;
    }
}

void Player::deccelerate()
{
    speed -= SPACESHIP_ACCELERATION;
    if (speed < 0)
    {
        speed = 0;
    }
}

void Player::normalize()
{
    if (x < 0)
    {
        x = 0;
    }
    else if (x > WINDOW_WIDTH - SPACESHIP_WIDTH)
    {
        x = WINDOW_WIDTH - SPACESHIP_WIDTH;
    }
    if (y < 0)
    {
        y = 0;
    }
    else if (y > WINDOW_HEIGHT - SPACESHIP_HEIGHT)
    {
        y = WINDOW_HEIGHT - SPACESHIP_HEIGHT;
    }
}