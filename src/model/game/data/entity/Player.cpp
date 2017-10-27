#include <iostream>
#include "Player.h"
#include "../../../../view/View.h"

Player::Player(): Entity()
{
    id = PLAYER;
    HP = maxHP = 100;
    xSpeed = ySpeed = 2;
}

void Player::init(long double x, long double y)
{
    this->x = x;
    this->y = y + 98;
}

void Player::up(long double ticks)
{
    y += ySpeed * ticks;
    if (y > WINDOW_HEIGHT + 98)
    {
        y = WINDOW_HEIGHT + 98;
    }
}

void Player::down(long double ticks)
{
    y -= ySpeed * ticks;
    if (y < 98*2)
    {
        y = 98*2;
    }
}

void Player::left(long double ticks)
{
    x -= xSpeed * ticks;
    if (x < 0)
    {
        x = 0;
    }
}

void Player::right(long double ticks)
{
    x += xSpeed * ticks;
    if (x > WINDOW_WIDTH - 56)
    {
        x = WINDOW_WIDTH - 56;
    }
}