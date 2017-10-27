#ifndef PROXIMACENTAURI_PLAYER_H
#define PROXIMACENTAURI_PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    void init(long double x, long double y);
    ~Player() = default;
    void up(long double ticks);
    void down(long double ticks);
    void left(long double ticks);
    void right(long double ticks);
};

#endif //PROXIMACENTAURI_PLAYER_H
