#include <iostream>
#include "Player.h"
#include "../../../ProximaCentauri.h"

Player::Player()
{
    hp = PLAYER_HEALTH;
    x = (WINDOW_WIDTH - SPACESHIP_WIDTH) / 2;
    y = WINDOW_HEIGHT - SPACESHIP_HEIGHT - SPACESHIP_INITIAL_Y;
    speed = 0;
}

Player::~Player()
{

}

int_fast32_t Player::getX() const
{
    return static_cast<int_fast32_t>(x);
}

int_fast32_t Player::getY() const
{
    return static_cast<int_fast32_t>(y);
}

int_fast32_t Player::getHP() const
{
    return hp;
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
    u((lag / SQRT2) * lag);
    l((lag / SQRT2) * lag);
}

void Player::ur(long double lag)
{
    u((lag / SQRT2) * lag);
    r((lag / SQRT2) * lag);
}

void Player::dl(long double lag)
{
    d((lag / SQRT2) * lag);
    l((lag / SQRT2) * lag);
}

void Player::dr(long double lag)
{
    d((lag / SQRT2) * lag);
    r((lag / SQRT2) * lag);
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

void Player::damage(uint_fast32_t damage)
{
    if (hp > damage)
    {
        hp -= damage;
    }
    else
    {
        hp = 0;
    }
}

bool Player::isAlive()
{
    return hp > 0;
}